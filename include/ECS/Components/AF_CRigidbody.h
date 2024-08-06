#ifndef AF_CRIGIDBODY_H
#define AF_CRIGIDBODY_H
#include "AF_Lib_Define.h"
#include "AF_CCollider.h"
#include "AF_Vec3.h"
#ifdef __cplusplus
extern "C" {    
#endif

/*
====================
AF_CRigidbody 
Component used to contain data for physics
====================
*/
typedef struct {
    BOOL has;
    BOOL enabled;
    BOOL isKinematic;
    float gravity;
    AF_Vec3 velocity;
} AF_CRigidbody;

/*
====================
AF_CRigidbody_ZERO
Empty constructor for the CRigidbody component
====================
*/
static inline AF_CRigidbody AF_CRigidbody_ZERO(void){
	AF_CRigidbody rigidbody = {
		.has = false,
		.enabled = false,
		.isKinematic = false,
		.velocity = {0.0f, 0.0f, 0.0f},
		.gravity = 0.0f
	};
	return rigidbody;
}

/*
====================
AF_CRigidbody_ADD
Add the CRigidbody component
enable the component and set some values to default values.
====================
*/
static inline AF_CRigidbody AF_CRigidbody_ADD(void){
	AF_CRigidbody rigidbody = {
		.has = true,
		.enabled = true,
		.isKinematic = false,			// isKinematic means to be controlled by script rather than the velocity
		.velocity = {0.0f, 0.0f, 0.0f},		// zero velocity 
		.gravity = 0.0f				// gravity off by default
	};
	return rigidbody;
}



#ifdef __cplusplus
}
#endif

#endif //AF_CRIGIDBODY_H

