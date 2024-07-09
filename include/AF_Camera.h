#ifndef AF_CAMERA_H
#define AF_CAMERA_H
#include "AF_CTransform3D.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  {
    AF_CTransform3D transform;
    AF_Vec3 cameraPosition;
    AF_Vec3 cameraFront;
    float yaw;
    float pitch;
} AF_CCamera;

// Function that takes a CTransform3D object
inline static AF_Vec3 AF_Camera_CalculateFront(AF_Vec3 _front) {
   
    /*
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)ı) * cos(glm::radians(pitch));
    */
    return AFV3_NORMALIZE(_front);
} 



#ifdef __cplusplus
}
#endif

#endif //AF_CAMERA_H
