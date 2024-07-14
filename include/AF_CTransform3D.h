#ifndef AF_TRANSFORM3D_H
#define AF_TRANSFORM3D_H
#include "AF_Vec3.h"
#include "AF_Lib_Define.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    BOOL has;// = FALSE;
    BOOL enabled;// = FALSE;
    AF_Vec3 pos;// = {0.0f, 0.0f, 0.0f};
    AF_Vec3 rot;// = {0.0f, 0.0f, 0.0f};
    AF_Vec3 scale;// = {1.0f, 1.0f, 1.0f};
} AF_CTransform3D;


#ifdef __cplusplus
}
#endif

#endif  // AF_TRANSFORM3D_H
