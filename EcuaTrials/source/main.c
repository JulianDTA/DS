#include <nds.h>
#include <stdio.h>
#include "game.h"
#include "graphics.h"

// =====================================================
// ECUATRIALS - Punto de Entrada Principal
// Usa ambas pantallas con consolas de texto separadas
// =====================================================

static GameState gameState;

void init_hardware() {
    // Pantalla Superior (Main): Fondos 2D y Sprites
    videoSetMode(MODE_0_2D | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D);
    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankB(VRAM_B_MAIN_SPRITE);
    
    // Pantalla Inferior (Sub): Fondos 2D y Sprites
    videoSetModeSub(MODE_0_2D | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D);
    vramSetBankC(VRAM_C_SUB_BG);
    vramSetBankD(VRAM_D_SUB_SPRITE);
    
    // Inicializar OAM
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    oamInit(&oamSub, SpriteMapping_1D_32, false);
    
    gfx_init();
    BG_PALETTE_SUB[0] = RGB15(31, 0, 0); // Red backdrop
    BG_PALETTE[0] = RGB15(0, 0, 31); // Blue backdrop
}

int main(void) {
    init_hardware();
    game_init(&gameState);

    while (1) {
        swiWaitForVBlank();
        
        // Actualizar hardware OAM
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
        
        scanKeys();

        int keys = keysDown();
        touchPosition touch;
        touchRead(&touch);

        // Actualizar logica
        game_update(&gameState, keys, &touch);

        // Dibujar pantalla superior (Main)
        game_draw_top(&gameState);

        // Dibujar pantalla inferior (Sub)
        game_draw_bottom(&gameState);
    }

    return 0;
}
