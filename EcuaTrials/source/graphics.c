#include "graphics.h"
#include <nds.h>

u16* gfx_card_gfx_mem;

void gfx_init() {
    // Apuntar directamente a la base de la VRAM_D
    gfx_card_gfx_mem = (u16*)0x06200000;
    
    // Configurar Paletas (4bpp = 16 colores por paleta)
    // Paleta 0: Blanco
    SPRITE_PALETTE_SUB[0 * 16 + 1] = RGB15(31, 31, 31);
    SPRITE_PALETTE_SUB[0 * 16 + 2] = RGB15(15, 15, 15);
    
    // Paleta 1: Rojo (Ataque)
    SPRITE_PALETTE_SUB[1 * 16 + 1] = RGB15(31, 0, 0);
    SPRITE_PALETTE_SUB[1 * 16 + 2] = RGB15(15, 0, 0);
    
    // Paleta 2: Azul (Escudo)
    SPRITE_PALETTE_SUB[2 * 16 + 1] = RGB15(0, 0, 31);
    SPRITE_PALETTE_SUB[2 * 16 + 2] = RGB15(0, 0, 15);
    
    // Paleta 3: Verde (Cura)
    SPRITE_PALETTE_SUB[3 * 16 + 1] = RGB15(0, 31, 0);
    SPRITE_PALETTE_SUB[3 * 16 + 2] = RGB15(0, 15, 0);
    
    // Paleta 4: Morado (Otro)
    SPRITE_PALETTE_SUB[4 * 16 + 1] = RGB15(31, 0, 31);
    SPRITE_PALETTE_SUB[4 * 16 + 2] = RGB15(15, 0, 15);
    
    // Dibujar sprite 32x64 en 4bpp agrupado por tiles de 8x8
    u16* vram = gfx_card_gfx_mem;
    
    for (int ty = 0; ty < 8; ty++) {       // 8 tiles de alto
        for (int tx = 0; tx < 4; tx++) {   // 4 tiles de ancho
            for (int y = 0; y < 8; y++) {
                // Cada fila de 8 pixeles en 4bpp son 4 bytes = 2 u16
                u16 word1 = 0;
                u16 word2 = 0;
                for (int x = 0; x < 8; x++) {
                    int px = tx * 8 + x;
                    int py = ty * 8 + y;
                    
                    int color = 1; // Centro
                    if (px == 0 || px == 31 || py == 0 || py == 63) {
                        color = 2; // Borde
                    }
                    
                    if (x < 4) {
                        word1 |= (color << (x * 4));
                    } else {
                        word2 |= (color << ((x - 4) * 4));
                    }
                }
                *vram++ = word1;
                *vram++ = word2;
            }
        }
    }
}
