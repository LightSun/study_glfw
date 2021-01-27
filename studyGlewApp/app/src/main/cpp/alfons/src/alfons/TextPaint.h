//
// Created by Administrator on 2021/1/27 0027.
//

#ifndef STUDYGLEWAPP_TEXTPAINT_H
#define STUDYGLEWAPP_TEXTPAINT_H

#define DEFAULT_TEXT_SIZE 20

/**
 * by heaven7
 */
namespace alfons {

    struct TextPaint {
        float textSize;
        bool drawUnderline;
        bool drawDeleteLine;
        int underlineColor;
        int deleteLineColor;
        float glyphSpace;
        float lineSpace;

        TextPaint(){
            textSize = DEFAULT_TEXT_SIZE;
            drawUnderline = false;
            drawDeleteLine = false;
            glyphSpace = 0;
            lineSpace = 0;
        }

        inline float getScale() const {
            return textSize / DEFAULT_TEXT_SIZE;
        }
    };
}

#endif //STUDYGLEWAPP_TEXTPAINT_H
