//
// Created by Administrator on 2021/1/23 0023.
//

#include <iostream>
#include <ctime>
#include "SimpleFontRender.h"

#include "hbshaper.h"
#include "freetypelib.h"
#include "log.h"

using namespace std;

vector<gl::Mesh*> meshes;

HBText hbt1;
HBText hbt2;
HBText hbt3;
HBText hbt4;
HBText hbt5;

static FreeTypeLib _xlib;

HBShaper latinShaper;
HBShaper arabicShaper;
HBShaper russianShaper;
HBShaper hanShaper;
HBShaper hindiShaper;

clock_t _begin, _end;
/*int main(int argc, char** argv) {
    srand(time(NULL));

    // the font rasterizing library
    FreeTypeLib lib;
    clock_t begin, end;

    HBShaper latinShaper("DejaVuSerif.ttf", &lib);
    HBShaper arabicShaper("amiri-regular.ttf", &lib);
    HBShaper russianShaper("DejaVuSerif.ttf", &lib);
    HBShaper hanShaper("fireflysung.ttf", &lib);
    HBShaper hindiShaper("Sanskrit2003.ttf", &lib);

    latinShaper.init();
    arabicShaper.init();
    russianShaper.init();
    hanShaper.init();
    hindiShaper.init();

    HBText hbt1 = {
        "ficellé fffffi. VAV.",
        "fr",
        HB_SCRIPT_LATIN,
        HB_DIRECTION_LTR
    };

    HBText hbt2 = {
        "تسجّل يتكلّم",
        "ar",
        HB_SCRIPT_ARABIC,
        HB_DIRECTION_RTL
    };

    HBText hbt3 = {
        "Дуо вёжи дёжжэнтиюнт ут",
        "ru",
        HB_SCRIPT_CYRILLIC,
        HB_DIRECTION_LTR
    };

    HBText hbt4 = {
        "緳 踥踕中国",
        "ch",
        HB_SCRIPT_HAN,
        HB_DIRECTION_TTB
    };

    HBText hbt5 = {
        "हालाँकि प्रचलित रूप पूजा",
        "hi",
        HB_SCRIPT_DEVANAGARI,
        HB_DIRECTION_LTR
    };

    latinShaper.addFeature(HBFeature::KerningOn);

    //gl::initGL(argc, argv);

    begin = clock();

    // ask for some meshes, this is not optimal since every glyph has its
    // own texture, should use an atlas than contains glyph inside
    //       ->>>>>>> e.g. DON'T DO THIS <<<<<<<<<-
    for(auto mesh: latinShaper.drawText(hbt1, 20, 320)) {
        meshes.push_back(mesh);
    }

    for(auto mesh: arabicShaper.drawText(hbt2, 20, 220)) {
        meshes.push_back(mesh);
    }

    for(auto mesh: russianShaper.drawText(hbt3, 20, 120)) {
        meshes.push_back(mesh);
    }

    for(auto mesh: hanShaper.drawText(hbt4, 700, 380)) {
        meshes.push_back(mesh);
    }

    for(auto mesh: hindiShaper.drawText(hbt5, 20, 20)) {
        meshes.push_back(mesh);
    }
    end = clock();

    std::cout << ((float) (end - begin) / CLOCKS_PER_SEC) * 1000 << " ms." << std::endl;

    gl::uploadMeshes(meshes);

    gl::loop(meshes);
    gl::finish();

    gl::deleteMeshes(meshes);

    return 0;
}*/

void SimpleFontRender::init(const char *fontDir) {
    srand(time(NULL));

    clock_t begin, end;

    MERGE_STR2(fontDir, "DejaVuSerif.ttf", latinShaper.set(ch, &_xlib));
    MERGE_STR2(fontDir, "amiri-regular.ttf", arabicShaper.set(ch, &_xlib));
    MERGE_STR2(fontDir, "DejaVuSerif.ttf", russianShaper.set(ch, &_xlib));
    MERGE_STR2(fontDir, "fireflysung.ttf", hanShaper.set(ch, &_xlib));
    MERGE_STR2(fontDir, "Sanskrit2003.ttf", hindiShaper.set(ch, &_xlib));

    latinShaper.init();
    arabicShaper.init();
    russianShaper.init();
    hanShaper.init();
    hindiShaper.init();

    hbt1.set(
            "ficellé fffffi. VAV.",
            "fr",
            HB_SCRIPT_LATIN,
            HB_DIRECTION_LTR
    );

    hbt2.set(
            "تسجّل يتكلّم",
            "ar",
            HB_SCRIPT_ARABIC,
            HB_DIRECTION_RTL
    );

    hbt3.set(
            "Дуо вёжи дёжжэнтиюнт ут",
            "ru",
            HB_SCRIPT_CYRILLIC,
            HB_DIRECTION_LTR
    );

    hbt4.set(
            "緳 踥踕中国",
            "ch",
            HB_SCRIPT_HAN,
            HB_DIRECTION_TTB
    );

    hbt5.set(
            "हालाँकि प्रचलित रूप पूजा",
            "hi",
            HB_SCRIPT_DEVANAGARI,
            HB_DIRECTION_LTR
    );

    latinShaper.addFeature(HBFeature::KerningOn);
    gl::createShaderProgram();

    //prepare font data
    meshes.clear();
    // ask for some meshes, this is not optimal since every glyph has its
    // own texture, should use an atlas than contains glyph inside
    //       ->>>>>>> e.g. DON'T DO THIS <<<<<<<<<-
    /* for(auto mesh: latinShaper.drawText(hbt1, 20, 320)) {
         meshes.push_back(mesh);
     }

     for(auto mesh: arabicShaper.drawText(hbt2, 20, 220)) {
         meshes.push_back(mesh);
     } */

    for(auto mesh: russianShaper.drawText(hbt3, 20, 120)) {
        meshes.push_back(mesh);
    }

    for(auto mesh: hanShaper.drawText(hbt4, 100, 100)) {
        meshes.push_back(mesh);
    }
/*
    for(auto mesh: hindiShaper.drawText(hbt5, 20, 20)) {
        meshes.push_back(mesh);
    }*/
    gl::uploadMeshes(meshes);
}
void SimpleFontRender::resize(long ptr, int width, int height) {
    gl::initGL(width, height);
}
void SimpleFontRender::draw() {
    _begin = clock();

    gl::render(meshes);
    //gl::deleteMeshes(meshes);

    _end = clock();

    LOGD("%df ms", ((float) (_end - _begin) / CLOCKS_PER_SEC) * 1000);
}
void SimpleFontRender::destroy() {
    gl::finish();
    gl::deleteMeshes(meshes);
}