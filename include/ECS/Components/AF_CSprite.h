#ifndef AF_CSPRITE_H
#define AF_CSPRITE_H
#include "AF_Vec2.h"
#include "AF_Material.h"
#ifdef __cplusplus
extern "C" {    
#endif
/*
====================
AF_CSprite
====================
*/

typedef struct {
	BOOL has;
	BOOL enabled;
	AF_Vec2 pos;
	AF_Vec2 size;
	int currentFrame;
	int animationFrames;
} AF_CSprite;

/*
====================
AF_CSprite_ZERO
Empty constructor for the AF_CSprite component
====================
*/
static inline AF_CSprite AF_CSprite_ZERO(void){
	AF_CSprite returnSprite = {
		.has = false,
		.enabled = false,
		.pos = {0.0f, 0.0f},
		.size = {0.0f, 0.0f},
		.currentFrame = 0,
		.animationFrames = 0,
	};
	return returnSprite;
}

/*
====================
AF_CSprite_ADD
ADD component and set default values
====================
*/
static inline AF_CSprite AF_CSprite_ADD(void){
	AF_CSprite returnSprite = {
		.has = true,
		.enabled = true,
		.pos = {0.0f, 0.0f},
		.size = {0.0f, 0.0f},
		.currentFrame = 0,
		.animationFrames = 0,
	};
	return returnSprite;
}



#ifdef __cplusplus
}
#endif

#endif //AF_CSPRITE_H

