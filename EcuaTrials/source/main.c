#include <nds.h>
#include <stdio.h>
#include "game.h"

// =====================================================
// ECUATRIALS - Punto de Entrada Principal
// =====================================================

static GameState gameState;
static PrintConsole bottomConsole;

void init_hardware() {
    // Pantalla Superior: 3D (para futuros sprites)
    videoSetMode(MODE_0_3D);
    
    // Pantalla Inferior: Consola de texto
    videoSetModeSub(MODE_0_2D);
    
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankC(VRAM_C_SUB_BG);
    
    // Motor 3D
    glInit();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof32(0, 256, 192, 0, -1, 1);
    glClearColor(2, 2, 6, 31); // Azul oscuro de fondo
    glClearPolyID(63);
    glClearDepth(0x7FFF);
    glViewport(0, 0, 255, 191);
    
    // Consola de texto en la pantalla inferior
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
        
        // Actualizar logica del juego
        game_update(&gameState, keys, &touch);
        
        // Redibujar la interfaz
        game_draw(&gameState);
        
        // Render 3D (preparado para futuros sprites)
        glFlush(0);
    }
    
    return 0;
}
