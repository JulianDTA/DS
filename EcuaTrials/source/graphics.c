#include <stdio.h>
#include "graphics.h"
#include <nds.h>

u16* gfx_cantuna;
u16* gfx_tunda;
PrintConsole* topConsole;
PrintConsole* subConsole;

#include "bg_top.h"
#include "bg_bottom.h"
#include "spr_card_back.h"
#include "spr_cantuna.h"
#include "spr_tunda.h"

u16* gfx_card_gfx_mem;

void gfx_init() {


    // Inicializar consola superior (HP)
    topConsole = consoleInit(NULL, 3, BgType_Text4bpp, BgSize_T_256x256, 4, 6, true, true);
    bgSetPriority(topConsole->bgId, 0);
    // Configurar color de texto
    BG_PALETTE[255] = RGB15(31, 31, 31); // Blanco
    BG_PALETTE[240] = 0; // Transparente
    
    // Inicializar consola inferior (Lore)

    // mapBase 4 (8KB), tileBase 6 (96KB). Usa los colores 240-255.

    subConsole = consoleInit(NULL, 3, BgType_Text4bpp, BgSize_T_256x256, 4, 6, false, true);
    bgSetPriority(subConsole->bgId, 0);

        bgSetPriority(subConsole->bgId, 0);

    // 1. Cargar Reverso de Carta (Sub, 8bpp)
    gfx_card_gfx_mem = oamAllocateGfx(&oamSub, SpriteSize_32x64, SpriteColorFormat_256Color);
    if (gfx_card_gfx_mem) {
        dmaCopy(spr_card_backTiles, gfx_card_gfx_mem, spr_card_backTilesLen);
    }
    dmaCopy(spr_card_backPal, SPRITE_PALETTE_SUB, spr_card_backPalLen);
    
    // Crear el Icono de Estado (16x16, 8bpp = 256 bytes)
    

    
    // Paletas para los iconos (Indices 1 a 4)
        
    // 2. Cargar Retratos (Main, 8bpp)
    gfx_cantuna = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);
    if (gfx_cantuna) {
        dmaCopy(spr_cantunaTiles, gfx_cantuna, spr_cantunaTilesLen);
    }
    gfx_tunda = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);
    if (gfx_tunda) {
        dmaCopy(spr_tundaTiles, gfx_tunda, spr_tundaTilesLen);
    }
    dmaCopy(spr_tundaPal, SPRITE_PALETTE, spr_tundaPalLen);

    // 3. Cargar Fondos
    int bg_top_id = bgInit(0, BgType_Text8bpp, BgSize_T_256x256, 0, 1);
    bgSetPriority(bg_top_id, 3);
    dmaCopy(bg_topTiles, bgGetGfxPtr(bg_top_id), bg_topTilesLen);
    dmaCopy(bg_topMap, bgGetMapPtr(bg_top_id), bg_topMapLen);
    dmaCopy(bg_topPal, BG_PALETTE, 480); // Main no tiene consola, asi que 512 esta bien. // Ya podemos usar los 512 porque no hay texto
    
    int bg_bot_id = bgInitSub(0, BgType_Text8bpp, BgSize_T_256x256, 0, 1);
    bgSetPriority(bg_bot_id, 3);
    dmaCopy(bg_bottomTiles, bgGetGfxPtr(bg_bot_id), bg_bottomTilesLen);
    dmaCopy(bg_bottomMap, bgGetMapPtr(bg_bot_id), bg_bottomMapLen);
    dmaCopy(bg_bottomPal, BG_PALETTE_SUB, 480);
    
    BG_PALETTE_SUB[255] = RGB15(12, 7, 3); // Default -> Cafe oscuro

}