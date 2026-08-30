
//{{BLOCK(board_bg)

//======================================================================
//
//	board_bg, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 682 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 43648 + 2048 = 46208
//
//	Time-stamp: 2026-08-30, 21:41:28
//	Exported by Cearn's GBA Image Transmogrifier, v1.23.0
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BOARD_BG_H
#define GRIT_BOARD_BG_H

#define board_bgTilesLen 43648
extern const unsigned int board_bgTiles[10912];

#define board_bgMapLen 2048
extern const unsigned short board_bgMap[1024];

#define board_bgPalLen 512
extern const unsigned short board_bgPal[256];

#endif // GRIT_BOARD_BG_H

//}}BLOCK(board_bg)
