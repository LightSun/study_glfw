//
// Created by Administrator on 2021/1/27 0027.
//

#ifndef STUDYGLEWAPP_LINERENDER_H
#define STUDYGLEWAPP_LINERENDER_H

#include <cstdint>
#include <vector>
#include <glm/detail/type_mat.hpp>
#include <render/GLUtils.h>

#include "gl.h"

/**
 * by heaven7
 */
namespace alfons {

    namespace draw{
        class GLShape {
        public:
            int color; //rgba
            float strokeWidth;
            GLShape(){}
            GLShape(int color, float strokeWidth): color(color), strokeWidth(strokeWidth) {
            }
            inline void setColorF(float r, float g, float b, float a) {
                color = clamp(r * 255) << 24
                        | clamp(g * 255) << 16
                        | clamp(b * 255) << 8
                        | clamp(a * 255);
            }
            inline static int clamp(float value) {
                int val = (int) (value);
                if (val < 0) {
                    val = 0;
                }
                if (val > 255) {
                    val = 255;
                }
                return val;
            }

            inline float r() {
                return ((color >> 24) & 0xff) * 1.0f / 255;
            }

            inline float g() {
                return ((color >> 16) & 0xff) * 1.0f / 255;
            }

            inline float b() {
                return ((color >> 8) & 0xff) * 1.0f / 255;
            }

            inline float a() {
                return ((color) & 0xff) * 1.0f / 255;
            }

            inline void getColor(float out[4]) {
                out[0] = r();
                out[1] = g();
                out[2] = b();
                out[3] = a();
            }
        };

        struct Rect: public GLShape{
            float vertexes[12];

            Rect(){}
            Rect(int color, float strokeWidth): GLShape(color, strokeWidth) {
            }
            void setRect(int left, int top, int right, int bottom){
                //drawOrder[6] = { 0, 1, 2, 0, 2, 3 }
                // left top
                // left bottom
                // right bottom
                // right top
                vertexes[0] = left;
                vertexes[1] = top;
                vertexes[2] = 0;

                vertexes[3] = left;
                vertexes[4] = bottom;
                vertexes[5] = 0;

                vertexes[6] = right;
                vertexes[7] = bottom;
                vertexes[8] = 0;

                vertexes[9] = right;
                vertexes[10] = top;
                vertexes[11] = 0;
            }
            float left(){
                return vertexes[0];
            }
            float top(){
                return vertexes[1];
            }
            float right(){
                return vertexes[6];
            }
            float bottom(){
                return vertexes[7];
            }
        };

        struct Line : public GLShape{
            float vertexes[6];

            Line(float _vert[6], int color, float strokeWidth):
                    GLShape(color, strokeWidth) {
                for (int i = 0; i < 6; ++i) {
                    vertexes[i] = _vert[i];
                }
            }
            Line(){};

            inline void setVertexes(float _vertexes[6]){
                for (int i = 0; i < 6; ++i) {
                    vertexes[i] = _vertexes[i];
                }
            }
            inline void setVertexes(float x1, float y1, float x2, float y2){
                vertexes[0] = x1;
                vertexes[1] = y1;
                vertexes[2] = 0;
                vertexes[3] = x2;
                vertexes[4] = y2;
                vertexes[5] = 0;
            }
        };
    }

    //https://cloud.tencent.com/developer/ask/90787 shader 绘制线条
    class LineRender {
    private:
        static constexpr const char *VertexShaderCode =
                // This matrix member variable provides a hook to manipulate
                // the coordinates of the objects that use this vertex shader
                "uniform mat4 uMVPMatrix;"
                "attribute vec4 vPosition;"
                "void main() {"
                // the matrix must be included as a modifier of gl_Position
                "  gl_Position = uMVPMatrix * vPosition;"
                "}";

        static constexpr const char *FragmentShaderCode =
                "precision mediump float;"
                "uniform vec4 vColor;"
                "void main() {"
                "  gl_FragColor = vColor;"
                "}";

        GLint PositionHandle;
        GLint ColorHandle;
        GLint MVPHandle;

        // number of coordinates per vertex in this array
        static constexpr int COORDS_PER_VERTEX = 3;
        static constexpr int VertexCount = 6 / COORDS_PER_VERTEX;
        static constexpr int VertexStride = COORDS_PER_VERTEX * 4; // 4 bytes per vertex

        std::vector<draw::Line> lines;
        std::vector<draw::Rect> fillRects;
        static constexpr short RectOrder[6] = { 0, 1, 2, 0, 2, 3 };

        int width, height;
        GLUT::Shader* shader;

    public:
        void init();

        void setViewPort(int w, int h);

        void addRect(draw::Rect& rect,bool fill); //stroke or fill

        void clearLines();

        void addLine(draw::Line &line);

        template <class... _Args>
        void addLineEmplace(_Args&&... args){
            lines.emplace_back(std::forward<_Args>(args)...);
        }
        void draw();
        void destroy();
    };
}

#endif //STUDYGLEWAPP_LINERENDER_H
