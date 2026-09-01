#include "graphics.h"
#include <nds.h>

#include "bg_top.h"
#include "bg_bottom.h"
#include "spr_card_back.h"
#include "spr_cantuna.h"
#include "spr_tunda.h"

u16* gfx_card_gfx_mem;

void gfx_init() {
    // 1. Cargar reverso de carta en OAM (Sub)
    // 8bpp = 256 colors
    gfx_card_gfx_mem = oamAllocateGfx(&oamSub, SpriteSize_32x64, SpriteColorFormat_256Color);
    if (gfx_card_gfx_mem) {
        dmaCopy(spr_card_backTiles, gfx_card_gfx_mem, spr_card_backTilesLen);
    }
    
    // Cargar la paleta del sprite (256 colores)
    dmaCopy(spr_card_backPal, SPRITE_PALETTE_SUB, spr_card_backPalLen);
    
    // 2. Cargar Fondo Superior (Main)
    int bg_top_id = bgInit(0, BgType_Text8bpp, BgSize_T_256x256, 0, 1);
    dmaCopy(bg_topTiles, bgGetGfxPtr(bg_top_id), bg_topTilesLen);
    dmaCopy(bg_topMap, bgGetMapPtr(bg_top_id), bg_topMapLen);
    dmaCopy(bg_topPal, BG_PALETTE, bg_topPalLen);
    
    // 3. Cargar Fondo Inferior (Sub)
    int bg_bot_id = bgInitSub(0, BgType_Text8bpp, BgSize_T_256x256, 0, 1);
    dmaCopy(bg_bottomTiles, bgGetGfxPtr(bg_bot_id), bg_bottomTilesLen);
    dmaCopy(bg_bottomMap, bgGetMapPtr(bg_bot_id), bg_bottomMapLen);
    dmaCopy(bg_bottomPal, BG_PALETTE_SUB, bg_bottomPalLen);
}
