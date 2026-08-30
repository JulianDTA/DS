#include <nds.h>
#include <stdio.h>

int main(void) {
    // ---------------------------------------------------------
    // 1. Inicialización Dual del Hardware
    // ---------------------------------------------------------
    
    // Pantalla Superior: Configurar el motor principal para 3D (MODE_0_3D)
    videoSetMode(MODE_0_3D);
    
    // Pantalla Inferior: Configurar el motor secundario para 2D (MODE_0_2D)
    videoSetModeSub(MODE_0_2D);
    
    // ---------------------------------------------------------
    // 2. Gestión de VRAM (Video RAM)
    // ---------------------------------------------------------
    
    // Mapear el Banco A para texturas 3D (Pantalla Superior)
    vramSetBankA(VRAM_A_TEXTURE);
    
    // Mapear el Banco C para fondos (Backgrounds) del motor 2D (Pantalla Inferior)
    vramSetBankC(VRAM_C_SUB_BG);
    
    // ---------------------------------------------------------
    // 3. Configuración Inicial del Motor 3D
    // ---------------------------------------------------------
    
    // Inicializar el motor 3D
    glInit();
    
    // Configurar la cámara en proyección ortográfica (plana) 
    // Los parámetros son: top, bottom, left, right, near, far
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof32(0, 256, 192, 0, -1, 1); // Resolución de la pantalla de DS (256x192)
    
    // Configurar el color de limpieza (fondo) de la pantalla superior
    glClearColor(0, 0, 0, 31);
    glClearPolyID(63);
    glClearDepth(0x7FFF);
    glViewport(0, 0, 255, 191);
    
    // ---------------------------------------------------------
    // Bucle Principal (Game Loop)
    // ---------------------------------------------------------
    while (1) {
        // Sincronizar con el refresco de pantalla (60 FPS)
        swiWaitForVBlank();
        
        // --- Fase de Actualización Lógica ---
        // Leer input de los botones y la pantalla táctil
        scanKeys();
        // int keys = keysDown();
        // touchPosition touch;
        // touchRead(&touch);
        
        // --- Renderizado 3D (Pantalla Superior) ---
        // Aquí dibujaremos los Quads (polígonos planos) con nuestros sprites limpios
        
        // --- Renderizado 2D (Pantalla Inferior) ---
        // Aquí actualizaremos el OAM para mover las cartas en la mano
        
        // Enviar la lista de comandos 3D al hardware para dibujar
        glFlush(0);
    }
    
    return 0;
}
