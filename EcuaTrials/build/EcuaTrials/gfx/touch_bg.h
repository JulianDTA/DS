
//{{BLOCK(touch_bg)

//======================================================================
//
//	touch_bg, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 740 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 47360 + 2048 = 49920
//
//	Time-stamp: 2026-08-30, 19:30:56
//	Exported by Cearn's GBA Image Transmogrifier, v1.23.0
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TOUCH_BG_H
#define GRIT_TOUCH_BG_H

#define touch_bgTilesLen 47360
extern const unsigned int touch_bgTiles[11840];

#define touch_bgMapLen 2048
extern const unsigned short touch_bgMap[1024];

#define touch_bgPalLen 512
extern const unsigned short touch_bgPal[256];

#endif // GRIT_TOUCH_BG_H

//}}BLOCK(touch_bg)
