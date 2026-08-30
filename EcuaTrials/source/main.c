#include <nds.h>
#include <stdio.h>
#include "card.h"
#include "combat.h"

// Headers autogenerados por GRIT (mismo nombre que los PNG)
#include "touch_bg.h"
#include "board_bg.h"

bool isMainOnBottom = false;

void init_graphics() {
    // Configurar ambos motores para soportar fondos Bitmap de 8-bits
    videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE);
    videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE);
    
    // Asignar bancos de VRAM
    vramSetBankA(VRAM_A_TEXTURE); // 3D
    vramSetBankB(VRAM_B_MAIN_BG); // Fondo Pantalla Superior
    vramSetBankC(VRAM_C_SUB_BG);  // Fondo Pantalla Inferior
    
    // Cargar Fondo Táctil (UI)
    int bg3_sub = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
    dmaCopy(touch_bgBitmap, bgGetGfxPtr(bg3_sub), touch_bgBitmapLen);
    dmaCopy(touch_bgPal, BG_PALETTE_SUB, touch_bgPalLen);
    
    // Cargar Fondo del Tablero
    int bg3_main = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
    dmaCopy(board_bgBitmap, bgGetGfxPtr(bg3_main), board_bgBitmapLen);
    dmaCopy(board_bgPal, BG_PALETTE, board_bgPalLen);
    
    // Configurar Motor 3D (Se renderizará sobre el fondo Main)
    glInit();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof32(0, 256, 192, 0, -1, 1);
    
    // Alpha 0 = Transparente para poder ver el fondo 2D que pusimos atrás
    glClearColor(0, 0, 0, 0); 
    glClearPolyID(63);
    glClearDepth(0x7FFF);
    glViewport(0, 0, 255, 191);
}

int main(void) {
    init_graphics();
    init_combat();
    
    while (1) {
        swiWaitForVBlank();
        scanKeys();
        int keys = keysDown();
        
        if (keys & KEY_SELECT) {
            isMainOnBottom = !isMainOnBottom;
            if (isMainOnBottom) lcdMainOnBottom();
            else lcdMainOnTop();
        }
        
        glFlush(0);
    }
    return 0;
}
