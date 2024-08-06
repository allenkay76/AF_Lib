#ifndef AF_CCOLLIDER_H
#define AF_CCOLLIDER_H
#include "AF_Lib_Define.h"
#include "AF_Rect.h"
#ifdef __cplusplus
extern "C" {    
#endif

/*
====================
AF_CCollider Struct used for physics
====================
*/
typedef struct {
    BOOL has;
    BOOL enabled;
    AF_Rect bounds;
} AF_CCollider;

/*
====================
AF_CCollider_ZERO
Empty constructor for the component
====================
*/

static inline AF_CCollider AF_CCollider_ZERO(void){
	AF_CCollider collider = {
		.has = false,
		.enabled = false,
		.bounds = {
			0,	// x
			0,	// y
			0,	// width
			0	// height
		}
	};
	return collider;
}

/*
====================
AF_CCollider_ADD
Add the CCollider component
enable the component and set some values to default values.
====================
*/
static inline AF_CCollider AF_CCollider_ADD(void){
	AF_CRigidbody rigidbody = {
		.has = true,
		.enabled = true,
		.bounds = {
			0,	// x
			0,	// y
			0,	// width
			0	// height
		}
	};
	return rigidbody
}



#ifdef __cplusplus
}
#endif

#endif //AF_CCOLLIDER_H

