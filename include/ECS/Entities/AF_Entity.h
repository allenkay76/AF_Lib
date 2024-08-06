/*
===============================================================================
AF_Entity_H defninitions
The entity struct and helper functions
===============================================================================
*/

#ifndef AF_Entity_H
#define AF_Entity_H
#include "AF_ECS.h"
#include "AF_Lib_Define.h"

#include "ECS/Components/AF_CTransform3D.h"
#include "ECS/Components/AF_CSprite.h"
#include "ECS/Components/AF_CCamera.h"
#include "ECS/Components/AF_CRigidbody.h"

typedef struct {
    BOOL alive;			// Entity has been created
    BOOL enabled;		// Entity has ben enabled
    uint32_t id;		// id of the entity
    AF_CTransform3D transform;	// 3d transform component
    AF_CSprite sprite;		// sprite cmponent
    AF_CCamera camera;		// camera component
    AF_Mesh mesh;		// mesh component
    AF_CRigidbody rigidbody;		// rigidbody component
} AF_Entity;

#endif //AF_Entity_H
