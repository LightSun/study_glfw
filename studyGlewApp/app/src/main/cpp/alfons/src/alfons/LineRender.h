//
// Created by Administrator on 2021/1/27 0027.
//

#ifndef STUDYGLEWAPP_LINERENDER_H
#define STUDYGLEWAPP_LINERENDER_H

#include <cstdint>
#include <vector>
#include <glm/detail/type_mat.hpp>
#include <render/GLUtils.h>
#include "utils.h"

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
            inline void setRect(float left, float top, float right, float bottom){
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
            inline void setVertex2D(float x1, float y1, float x2, float y2,
                             float x11, float y11, float x22, float y22){
                vertexes[0] = x1;
                vertexes[1] = y1;
                vertexes[2] = 0;

                vertexes[3] = x2;
                vertexes[4] = y2;
                vertexes[5] = 0;

                vertexes[6] = x11;
                vertexes[7] = y11;
                vertexes[8] = 0;

                vertexes[9] = x22;
                vertexes[10] = y22;
                vertexes[11] = 0;
            }
            inline float left(){
                return vertexes[0];
            }
            inline float top(){
                return vertexes[1];
            }
            inline float right(){
                return vertexes[6];
            }
            inline float bottom(){
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
            inline void strokeRect(Rect& rect){
                float x1 = vertexes[0];
                float y1 = vertexes[1];
                float x2 = vertexes[3];
                float y2 = vertexes[4];
                if(x1 == x2){
                    rect.setRect(x1 - strokeWidth / 2, y1 - strokeWidth / 2, x1 + strokeWidth / 2, y2 + strokeWidth / 2);
                } else if(y1 == y2){
                    rect.setRect(x1 - strokeWidth / 2, y1 - strokeWidth / 2, x2 + strokeWidth / 2, y1 + strokeWidth / 2);
                } else{
                    float x11, y11, x22, y22;
                    float tan = fabs(y2 - y1) / fabs(x2- x1);
                    float radius = atan(tan);
                    float degree = toDegree(radius);
                    if(x1 < x2){
                        if(y1 > y2){
                            //    v11
                            //v1 /\
                            //   \ \
                            // v2 \/ v22
                            //sin(radius) = dx /stroke = sin(radius)
                            x11 = sin(radius) * strokeWidth + x1;
                            //sin = sin(toRadius(90 - degree)) = dy / stroke
                            y11 = sin(toRadius(90 - degree)) * strokeWidth + y1;
                            x22 = sin(radius) * strokeWidth + x2;
                            y22 = sin(toRadius(90 - degree)) * strokeWidth + y2;
                            rect.setVertex2D(x1, y1, x2, y2, x22, y22, x11, y11);
                        } else{
                            /*   v11
                                   /\ v2
                                  / /
                              v22 \/ v1
                             */
                            //sin(radius) = dx /stroke = sin(radius)
                            x11 = x2 - sin(radius) * strokeWidth;
                            //sin = sin(toRadius(90 - degree)) = dy / stroke
                            y11 = sin(toRadius(90 - degree)) * strokeWidth + y2;
                            x22 = x1 - sin(radius) * strokeWidth;
                            y22 = sin(toRadius(90 - degree)) * strokeWidth + y1;
                            rect.setVertex2D(x11, y11, x22, y22, x1, y1, x2, y2);
                        }
                    } else{
                        if(y1 > y2){
                            /*   v11
                                  /\ v1
                                 / /
                             v22 \/ v2
                            */
                            x11 = x1 - sin(radius) * strokeWidth;
                            y11 = sin(toRadius(90 - degree)) * strokeWidth + y1;
                            x22 = x2 - sin(radius) * strokeWidth;
                            y22 = sin(toRadius(90 - degree)) * strokeWidth + y2;
                            rect.setVertex2D(x11, y11, x22, y22, x2, y2, x1, y1);
                        } else{
                            //    v11
                            //v2 /\
                            //   \ \
                            // v1 \/ v22
                            x11 = sin(radius) * strokeWidth + x2;
                            y11 = sin(toRadius(90 - degree)) * strokeWidth + y2;
                            x22 = sin(radius) * strokeWidth + x1;
                            y22 = sin(toRadius(90 - degree)) * strokeWidth + y1;
                            rect.setVertex2D(x2, y2, x1, y1, x22, y22, x11, y11);
                        }
                    }
                }
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
