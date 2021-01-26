//#include "glfwloop.h"

#include "alfons/fontManager.h"
#include "alfons/textBatcher.h"
#include "alfons/textShaper.h"
#include "alfons/font.h"
#include "alfons/path/lineSampler.h"
#include "renderer.h"

#include "logger.h"
#include "demoRenderer.h"

#include "JNIRender.h"

#if 0
#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"
NVGcontext* vg = nullptr;

#endif

#define TEXT_SIZE 20
#define DEFAULT "NotoSans-Regular.ttf"
#define FONT_AR "NotoNaskh-Regular.ttf"
#define FONT_HE "NotoSansHebrew-Regular.ttf"
#define FONT_HI "NotoSansDevanagari-Regular.ttf"
#define FONT_JA "DroidSansJapanese.ttf"
#define FALLBACK "DroidSansFallback.ttf"

using namespace alfons;

DemoRenderer renderer;
FontManager fontMan;
GlyphAtlas atlas(renderer, 256, 2);
TextBatcher batch(atlas, renderer);
TextShaper shaper;
std::shared_ptr<Font> font;
std::vector<LineLayout> l;//all layout

static void addFace(const char *fontDir, const char *str) {
    auto ch = merge(fontDir, str);
    std::string cppStr(ch);
    font->addFace(fontMan.addFontFace(InputSource(cppStr), TEXT_SIZE));
    free(ch);
}

static void addFont(const char *fontDir, const char *str) {
    auto ch = merge(fontDir, str);
    std::string cppStr(ch);
    font = fontMan.addFont("default", Font::Properties(TEXT_SIZE), InputSource(cppStr));
    free(ch);
}

extern "C" void onSetup(const char *fontDir) {

    renderer.init();

    /* font = fontMan.addFont("default", Font::Properties(TEXT_SIZE), InputSource((std::string)DEFAULT));
     font->addFace(fontMan.addFontFace(InputSource((std::string)FONT_AR), TEXT_SIZE));
     font->addFace(fontMan.addFontFace(InputSource((std::string)FONT_HE), TEXT_SIZE));
     font->addFace(fontMan.addFontFace(InputSource((std::string)FONT_HI), TEXT_SIZE));
     font->addFace(fontMan.addFontFace(InputSource((std::string)FONT_JA), TEXT_SIZE));
     font->addFace(fontMan.addFontFace(InputSource((std::string)FALLBACK), TEXT_SIZE));*/
    addFont(fontDir, DEFAULT);
    addFace(fontDir, FONT_AR);
    addFace(fontDir, FONT_HE);
    addFace(fontDir, FONT_HI);
    addFace(fontDir, FONT_JA);
    addFace(fontDir, FALLBACK);


    l.push_back(shaper.shape(font, "Eß hatte aber alle Welt einerlei Zünge und Sprache."));
    l.push_back(shaper.shape(font,
                             "وَكَانَتِ الارْضُ كُلُّهَا لِسَانا وَاحِدا وَلُغَةً وَاحِدًَ.")); // ar
    l.push_back(shaper.shape(font, "ΚΑΙ ολόκληρη η γη ήταν μιας γλώσσας, και μιας φωνής.")); // el
    l.push_back(shaper.shape(font, "And the whole earth was of one language, and of one speech."));
    l.push_back(shaper.shape(font,
                             "ERA entonces toda la tierra de una lengua y unas mismas palabras."));
    l.push_back(shaper.shape(font, "Toute la terre avait une seule langue et les mêmes mots."));

    l.push_back(shaper.shape(font, "nוַיְהִי כָל-הָאָרֶץ, שָׂפָה אֶחָת, וּדְבָרִים, אֲחָדִים.")); //he
    l.push_back(shaper.shape(font, "सारी पृथ्वी पर एक ही भाषा, और एक ही बोली थी।")); // hi
    l.push_back(shaper.shape(font, "全地は同じ発音、同じ言葉であった。")); //ja
    l.push_back(shaper.shape(font, "온 땅의 구음이 하나이요 언어가 하나이었더라")); //ko
    l.push_back(shaper.shape(font, "На всей земле был один язык и одно наречие."));

    std::string str = "那時、天下人的口音言語、都是一樣。\"的肌肤的肌肤mdfjdjfdfjdfjdfjdfdjskfafk，dfdf\"好烦好烦。dsfsdjsfjsfj，adada对符合当时发生的符合。";
    l.push_back(shaper.shape(font, str)); //zh-tw

    str = "那時、天下人的口音言語、都是一樣。\n的肌肤的肌肤mdfjdjfdfjdfjdfjdfdjskfafk， 好烦好烦。dsfsdjsfjsfj， 对符合当时发生的符合。";
    l.push_back(shaper.shape(font, str)); //zh-tw


    auto layout = shaper.shape(font, str);
    layout.setScale(2.0f);
    l.push_back(layout);
    // BIDI - RTL paragraph
    // l.push_back(shaper.shape(font, "ممم 26 يي\r\nيي 12\r\n34 ووووو end"));
    // BIDI - LTR paragraph
    //l.push_back(shaper.shape(font, "start محور 26 يوليو 42 يوليو end"));

#ifdef NANO_VG
    vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#endif
}

extern "C" void doTest0(int width, int height){
    auto layout = shaper.shape(font, "那時、天下人的口音言語、都是一樣。的肌肤的肌肤mdfjdjfdfjdfjdfjdfdjskfafk，"
                                     " 好烦好烦。dsfsdjsfjsfj， 对符合当时发生的符合。");
    float out[2];
    batch.measure(layout, width / 2.0f, height, out);
    LOGD("doTest0:  measure result wh = (%.2f, %.2f), width = %.2f, height = %d",
            out[0], out[1], width / 2.0f, height);
}
/**
 * 文字处理一般包括： 测量，绘制在指定宽度内, 颜色，
 * 粗体，斜体，下划线，删除线，等
 * 行间隔，字符间隔。左对齐，右对齐
 * 加载系统字体.
 */
extern "C" void onDraw(/*GLFWwindow *window, */int width, int height) {
#ifdef NANO_VG
    nvgBeginFrame(vg, width, height, 1);
    nvgStrokeColor(vg, nvgRGBA(255,255,255,128));
    nvgFillColor(vg, nvgRGBA(64,64,64,128));
#endif

    batch.setClip(0, 0, width, height);

    glm::vec2 offset(20, 20);

    for (auto &line : l) {

#ifdef NANO_VG
        float asc = line.ascent();
        float dsc = line.descent();
        float adv = line.advance();
        nvgBeginPath(vg);
        nvgMoveTo(vg, offset.x, offset.y - asc);
        nvgLineTo(vg, offset.x + adv, offset.y - asc);
        nvgLineTo(vg, offset.x + adv, offset.y + dsc);
        nvgLineTo(vg, offset.x, offset.y + dsc);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgMoveTo(vg, offset.x, offset.y);
        nvgLineTo(vg, offset.x + line.advance(), offset.y);
        nvgStroke(vg);
#endif

        //40: 左右各20
        offset.y = batch.draw(line, offset, std::max(width - 40, 10)).y;
        offset.y += 10;
    }

#ifdef NANO_VG
    nvgEndFrame(vg);
#endif

    renderer.beginFrame(width, height);//default setRange 0.3f-0.7f

    float inner = 0.1;
    float outer = 0.3;
    float outerCenter = 0.5 - inner;//0.4f

    //default is : (1.0, 1.0, 1.0, 1.0)
  /*  {  //option 1: 红色
        renderer.setColor({1.0, 0.0, 0.0, 1.0});
        renderer.setRange(outerCenter - outer, outerCenter + outer);
        renderer.draw();
    }

    {  //option 2: 黑色.
        renderer.setColor({0.0, 0.0, 0.0, 1.0});
        renderer.setRange(0.5 - inner, 0.5 + inner);
        renderer.draw();
    }*/

    {  //option 3: 红色
        renderer.setColor({1.0, 0.0, 0.0, 1.0});
       // renderer.setRange(0, 1);
        renderer.draw();
    }

    renderer.end();

}

/*int main() {
    glfwLoop();
    renderer.dispose();
    return 0;
}*/
