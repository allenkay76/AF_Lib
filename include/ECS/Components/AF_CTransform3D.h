#ifndef AF_TRANSFORM3D_H
#define AF_TRANSFORM3D_H
#include "AF_Vec3.h"
#include "AF_Lib_Define.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
====================
AF_CTransform3D
basic struct for the transform component
====================
*/
typedef struct {
    BOOL has;// = FALSE;
    BOOL enabled;// = FALSE;
    AF_Vec3 pos;// = {0.0f, 0.0f, 0.0f};
    AF_Vec3 rot;// = {0.0f, 0.0f, 0.0f};
    AF_Vec3 scale;// = {1.0f, 1.0f, 1.0f};
} AF_CTransform3D;

/*
====================
AF_CTransform3D_ZERO
Empty constructor
====================
*/
static inline AF_CTransform3D AF_CTransform3D_ZERO(void){
	AF_CTransform3D returnTransform = {
        .has = FALSE,
        .enabled = FALSE,
        .pos = {0.0f, 0.0f, 0.0f},
        .rot = {0.0f, 0.0f, 0.0f},
        .scale = {1.0f, 1.0f, 1.0f}
	// Default position matrix
    };
	return returnTransform;
}

/*
====================
AF_CTransform3D_ADD
Add component constructor for the component
====================
*/
static inline AF_CTransform3D AF_CTransform3D_ADD(void){
	AF_CTransform3D returnTransform = {
        .has = TRUE,
        .enabled = TRUE,
        .pos = {0.0f, 0.0f, 0.0f},
        .rot = {0.0f, 0.0f, 0.0f},
        .scale = {1.0f, 1.0f, 1.0f}
	// Default position matrix
    };
	return returnTransform;
}

#ifdef __cplusplus
}
#endif

#endif  // AF_TRANSFORM3D_H
