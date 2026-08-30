#include <nds.h>
#include <stdio.h>
#include "card.h"
#include "combat.h"

// Fondos
#include "touch_bg.h"
#include "board_bg.h"

// Texturas 3D
#include "cantuna_sprite.h"
#include "tintin_sprite.h"

bool isMainOnBottom = false;
PrintConsole bottomScreenConsole;

int cantuna_tex, tintin_tex;

void load_textures() {
    glGenTextures(1, &cantuna_tex);
    glBindTexture(0, cantuna_tex);
    glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_64, TEXTURE_SIZE_64, 0, TEXGEN_TEXCOORD, cantuna_spriteBitmap);
    
    glGenTextures(1, &tintin_tex);
    glBindTexture(0, tintin_tex);
    glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_64, TEXTURE_SIZE_64, 0, TEXGEN_TEXCOORD, tintin_spriteBitmap);
}

void init_graphics() {
    videoSetMode(MODE_0_3D | DISPLAY_BG3_ACTIVE | DISPLAY_BG0_ACTIVE);
    videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE | DISPLAY_BG0_ACTIVE);
    
    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankB(VRAM_B_TEXTURE);
    vramSetBankC(VRAM_C_SUB_BG);
    
    consoleInit(&bottomScreenConsole, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    
    int bg3_sub = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 4, 0);
    bgSetPriority(bg3_sub, 3);
    dmaCopy(touch_bgBitmap, bgGetGfxPtr(bg3_sub), touch_bgBitmapLen);
    dmaCopy(touch_bgPal, BG_PALETTE_SUB, touch_bgPalLen);
    
    int bg3_main = bgInit(3, BgType_Text8bpp, BgSize_T_256x256, 31, 0);
    bgSetPriority(bg3_main, 3);
    dmaCopy(board_bgTiles, bgGetGfxPtr(bg3_main), board_bgTilesLen);
    dmaCopy(board_bgMap, bgGetMapPtr(bg3_main), board_bgMapLen);
    dmaCopy(board_bgPal, BG_PALETTE, board_bgPalLen);
    
    // --- MOTOR 3D ---
    glInit();
    
    // Configurar texturas
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    
    // Color de transparencia
    glClearColor(0, 0, 0, 0); 
    glClearPolyID(63);
    glClearDepth(0x7FFF);
    glViewport(0, 0, 255, 191);
    
    load_textures();
}

void print_hud() {
    consoleSelect(&bottomScreenConsole);
    consoleClear();
    
    PlayerState* p1 = get_player_state(0);
    PlayerState* p2 = get_player_state(1);
    
    printf("\n\n\n\n\n\n\n"); 
    printf("        ECUA TRIALS\n\n");
    printf("   HP: %d/10      Escudo: %d\n", p1->hp, p1->shield);
    printf("   Energia: %d/10\n\n", p1->energy);
    printf("   RIVAL HP: %d/10  Esc: %d\n", p2->hp, p2->shield);
}

void draw_sprite(int tex, int x, int y) {
    glBindTexture(0, tex);
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);
    
    // IMPORTANTE: El color de los vértices se multiplica por la textura.
    // Si no definimos el color como Blanco (255,255,255), el motor asume 
    // que es Negro (0,0,0), lo que vuelve el polígono y la textura negros.
    glColor3b(255, 255, 255);
    
    glBegin(GL_QUADS);
    
    // Coordenadas UV a 64x64 pixeles (inttot16(64))
    GFX_TEX_COORD = TEXTURE_PACK(inttot16(0), inttot16(0));
    glVertex3v16(x - 32, y - 32, 0);
    
    GFX_TEX_COORD = TEXTURE_PACK(inttot16(0), inttot16(64));
    glVertex3v16(x - 32, y + 32, 0);
    
    GFX_TEX_COORD = TEXTURE_PACK(inttot16(64), inttot16(64));
    glVertex3v16(x + 32, y + 32, 0);
    
    GFX_TEX_COORD = TEXTURE_PACK(inttot16(64), inttot16(0));
    glVertex3v16(x + 32, y - 32, 0);
    
    glEnd();
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
        
        // --- Render 3D ---
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrthof32(0, 256, 192, 0, -1, 1);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Dibujar Cantuña a la izquierda
        draw_sprite(cantuna_tex, 64, 128);
        
        // Dibujar El Tin Tin a la derecha
        draw_sprite(tintin_tex, 192, 128);
        
        glFlush(0);
    }
    return 0;
}
