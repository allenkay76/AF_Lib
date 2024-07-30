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

typedef struct {
    BOOL active;
    uint32_t id;
    AF_CTransform3D transform;
    AF_CSprite sprite;
    AF_CCamera camera;
} AF_Entity;

#endif //AF_Entity_H
