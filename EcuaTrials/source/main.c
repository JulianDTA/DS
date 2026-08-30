#include <nds.h>
#include <stdio.h>
#include "card.h"
#include "combat.h"

// Headers autogenerados por GRIT
#include "touch_bg.h"
#include "board_bg.h"

bool isMainOnBottom = false;
PrintConsole topScreenConsole;
PrintConsole bottomScreenConsole;

void init_graphics() {
    // Motor Principal: 3D en la capa superior, y BG3 para el fondo de la plaza
    videoSetMode(MODE_0_3D | DISPLAY_BG3_ACTIVE | DISPLAY_BG0_ACTIVE);
    
    // Motor Secundario: 2D para la UI táctil y texto
    videoSetModeSub(MODE_0_2D | DISPLAY_BG3_ACTIVE | DISPLAY_BG0_ACTIVE);
    
    // Bancos de Memoria VRAM
    vramSetBankA(VRAM_A_TEXTURE); // Texturas 3D
    vramSetBankB(VRAM_B_MAIN_BG); // Fondos Main (Top)
    vramSetBankC(VRAM_C_SUB_BG);  // Fondos Sub (Bottom)
    
    // --- FONDO TABLERO TACTIL (Sub Engine) ---
    // Usamos BgType_Text8bpp porque Mode 0 lo exige
    int bg3_sub = bgInitSub(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);
    dmaCopy(touch_bgTiles, bgGetGfxPtr(bg3_sub), touch_bgTilesLen);
    dmaCopy(touch_bgMap, bgGetMapPtr(bg3_sub), touch_bgMapLen);
    dmaCopy(touch_bgPal, BG_PALETTE_SUB, touch_bgPalLen);
    
    // Consola de Texto para el HUD en Español (Sub Engine BG0)
    consoleInit(&bottomScreenConsole, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    
    // --- FONDO PLAZA 3D (Main Engine) ---
    int bg3_main = bgInit(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);
    dmaCopy(board_bgTiles, bgGetGfxPtr(bg3_main), board_bgTilesLen);
    dmaCopy(board_bgMap, bgGetMapPtr(bg3_main), board_bgMapLen);
    dmaCopy(board_bgPal, BG_PALETTE, board_bgPalLen);
    
    // --- MOTOR 3D ---
    glInit();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof32(0, 256, 192, 0, -1, 1);
    
    glClearColor(0, 0, 0, 0); // Transparente para que se vea la Plaza de San Francisco atrás
    glClearPolyID(63);
    glClearDepth(0x7FFF);
    glViewport(0, 0, 255, 191);
}

void print_hud() {
    consoleSelect(&bottomScreenConsole);
    consoleClear();
    
    PlayerState* p1 = get_player_state(0);
    PlayerState* p2 = get_player_state(1);
    
    printf("\n\n\n\n\n\n\n\n"); // Bajamos el texto para que cuadre con la madera
    printf("     === ECUA TRIALS ===\n\n");
    printf(" JUGADOR : HP %d/10 | Escudo %d\n", p1->hp, p1->shield);
    printf(" ENERGIA : %d/10\n\n", p1->energy);
    printf(" RIVAL   : HP %d/10 | Escudo %d\n", p2->hp, p2->shield);
}

int main(void) {
    init_graphics();
    init_combat();
    get_player_state(0)->energy = 10;
    
    print_hud();
    
    while (1) {
        swiWaitForVBlank();
        scanKeys();
        int keys = keysDown();
        
        if (keys & KEY_SELECT) {
            isMainOnBottom = !isMainOnBottom;
            if (isMainOnBottom) lcdMainOnBottom();
            else lcdMainOnTop();
        }
        
        if (keys & KEY_A) {
            play_card(0, &CartaDB[0]);
            print_hud();
        }
        if (keys & KEY_B) {
            play_card(0, &CartaDB[2]);
            print_hud();
        }
        
        glFlush(0);
    }
    return 0;
}
