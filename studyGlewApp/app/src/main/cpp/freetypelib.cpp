#include "freetypelib.h"
#include <cassert>
#include "log.h"

FreeTypeLib::FreeTypeLib() {
    FT_Init_FreeType(&lib);
}

FreeTypeLib::~FreeTypeLib() {
    FT_Done_FreeType(lib);
}

FT_Face* FreeTypeLib::loadFace(const char* fontName, int ptSize, int deviceHDPI, int deviceVDPI) {
    FT_Face* face = new FT_Face;

    LOGD("loadFace: %s", fontName);
    FT_Error error = FT_New_Face(lib, fontName, 0, face);
    assert(error == 0 && "Cannot open font file");

    force_ucs2_charmap(*face);
    FT_Set_Char_Size(*face, 0, ptSize, deviceHDPI, deviceVDPI);
// For Some Twisted Reason, FreeType Measures Font Size
    // In Terms Of 1/64ths Of Pixels.  Thus, To Make A Font
    // h Pixels High, We Need To Request A Size Of h*64.
    // (h << 6 Is Just A Prettier Way Of Writing h*64)
   // FT_Set_Char_Size( face, h << 6, h << 6, 96, 96);
    return face;
}

void FreeTypeLib::freeFace(FT_Face* face) {
    FT_Done_Face(*face);
    delete face;
}

void FreeTypeLib::freeGlyph(Glyph* glyph) {
    delete glyph;
}

int FreeTypeLib::force_ucs2_charmap(FT_Face ftf) {
    for(int i = 0; i < ftf->num_charmaps; i++) {
        if ((  (ftf->charmaps[i]->platform_id == 0)
            && (ftf->charmaps[i]->encoding_id == 3))
           || ((ftf->charmaps[i]->platform_id == 3)
            && (ftf->charmaps[i]->encoding_id == 1))) {
                return FT_Set_Charmap(ftf, ftf->charmaps[i]);
        }
    }
    return -1;
}

Glyph* FreeTypeLib::rasterize(FT_Face* face, uint32_t glyphIndex) const {
    Glyph* g = new Glyph;

    FT_Int32 flags =  FT_LOAD_DEFAULT;

    FT_Load_Glyph(*face,
        glyphIndex, // the glyph_index in the font file
        flags
    );

    FT_GlyphSlot slot = (*face)->glyph;
    FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

    FT_Bitmap ftBitmap = slot->bitmap;
    LOGD("FT_Bitmap pixformat: %d", ftBitmap.pixel_mode);

    g->buffer = ftBitmap.buffer;
    g->width = ftBitmap.width;
    g->height = ftBitmap.rows;
    g->bearing_x = slot->bitmap_left;
    g->bearing_y = slot->bitmap_top;

    return g;
}
