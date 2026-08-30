#include <nds.h>
#include <stdio.h>
#include "game.h"

// =====================================================
// ECUATRIALS - Punto de Entrada Principal
// Usa ambas pantallas con consolas de texto separadas
// =====================================================

static GameState gameState;
static PrintConsole topConsole;
static PrintConsole bottomConsole;

void init_hardware() {
    // Pantalla Superior: Consola de texto para lore/descripcion
    videoSetMode(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_BG);
    consoleInit(&topConsole, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

    // Pantalla Inferior: Consola de texto para HUD/mano
    videoSetModeSub(MODE_0_2D);
    vramSetBankC(VRAM_C_SUB_BG);
    consoleInit(&bottomConsole, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
}

int main(void) {
    init_hardware();
    game_init(&gameState);

    while (1) {
        swiWaitForVBlank();
        scanKeys();

        int keys = keysDown();
        touchPosition touch;
        touchRead(&touch);

        // Actualizar logica
        game_update(&gameState, keys, &touch);

        // Dibujar pantalla superior (lore de la carta)
        consoleSelect(&topConsole);
        game_draw_top(&gameState);

        // Dibujar pantalla inferior (HUD y mano)
        consoleSelect(&bottomConsole);
        game_draw_bottom(&gameState);
    }

    return 0;
}
