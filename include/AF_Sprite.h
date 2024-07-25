#ifndef AF_SPRITE_SHEET_H
#define AF_SPRITE_SHEET_H
#include "AF_Vec2.h"
#ifdef __cplusplus
extern "C" {    
#endif
/*
====================
AF_SPRITE_SHEET

====================
*/

typedef struct {
	AF_Vec2 pos;
	AF_Vec2 size;
	int currentFrame;
	int animationFrames;
	
} AF_Sprite;




#ifdef __cplusplus
}
#endif

#endif //AF_SPRITE_SHEET_H

