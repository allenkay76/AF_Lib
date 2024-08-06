#ifndef AF_CCAMERA_H
#define AF_CCAMERA_H
#include "AF_Math.h"
#include "ECS/Components/AF_CTransform3D.h"
#include "AF_Mat4.h"
#include "AF_Window.h"
#include <math.h> // Include math for std::tan
#include "AF_Lib_Define.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  {
    BOOL has;
    BOOL enabled;
    AF_Vec3 cameraFront;
    AF_Vec3 cameraUp;
    AF_Vec3 cameraRight;
    AF_Vec3 cameraWorldUp;
    float yaw;
    float pitch;
    float fov;
    float nearPlane;
    float farPlane;
    float aspectRatio;
    float windowWidth;
    float windowHeight;
    float tanHalfFov;
    float rangeInv;
    BOOL orthographic;
    AF_Mat4 projectionMatrix;
    AF_Mat4 viewMatrix;
    AF_Vec4 backgroundColor;
} AF_CCamera;

inline static AF_CCamera AF_CCamera_ZERO(void){
	AF_CCamera returnCamera = {
		.cameraFront = AFV3_ZERO(),
		.cameraUp = AFV3_ZERO(),
		.cameraRight = AFV3_ZERO(),
		.cameraWorldUp = AFV3_ZERO(),
		.yaw = 0.0f,
		.pitch = 0.0f,
		.fov = 0.0f,
		.nearPlane = 0.0f,
		.aspectRatio = 0.0f,
		.windowWidth = 0.0f,
		.windowHeight = 0.0f,
		.tanHalfFov = 0.0f,
		.rangeInv = 0.0f,
		.orthographic = false,
		.projectionMatrix = AFM4_IDENTITY(),
		.viewMatrix = AFM4_IDENTITY(),
		.backgroundColor = AFV4_ZERO()
	};

	return returnCamera;
}

inline static AF_CCamera AF_CCamera_ADD(BOOL _isOrthographic){
	AF_CCamera returnCamera = {
		.cameraFront = {0.0f, 0.0f, 1.0f},
		.cameraUp = {0.0f, 1.0f, 0.0f},
		.cameraRight =  {0.0f, 0.0f, 0.0f},
		.cameraWorldUp = {0.0f, 1.0f, 0.0f},
		.yaw = 0.0f,
		.pitch = 0.0f,
		.fov = 45.0f,
		.nearPlane = 0.01f,
		.farPlane = 100.0f,
		.aspectRatio = 0.0f,
		.windowWidth = 0.0f,
		.windowHeight = 0.0f,
		.tanHalfFov = tan(45.0f * 0.5f), //tan(halfFov)
		.rangeInv = 1.0f / 100.0f - 0.01f, // 1/farPlane - nearPlane
		.orthographic = _isOrthographic,
		.projectionMatrix = AFM4_IDENTITY(),
		.viewMatrix = AFM4_IDENTITY(),
		.backgroundColor = AFV4_ZERO()
	};
	return returnCamera;
}
	

inline static AF_Mat4 AF_Camera_GetOrthographicProjectionMatrix(AF_Window* _window, AF_CCamera* _camera){

   
       
   //https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix.html
    /*	// https://community.khronos.org/t/constructing-an-orthographic-matrix-for-2d-drawing/62270/5
	// General formula for orthographic projection
	x_max = viewport_width - 1.0;
	y_max = viewport_height - 1.0;
	x_new = 2.0 * x / x_max - 1.0;
	y_new = -(2.0 * y / y_max - 1.0);
	z_new = 2.0 * (z - zNear) / (zFar - zNear) - 1.0;
	w_new = 1.0;

    */

    	//float x_new = -(2.0f * x / x_max - 1.0f;
	//float y_new = -(2.0f * y / y_max - 1.0f);
	//float z_new = 2.0 * (z - _camera->nearPlane) / (_camera->farPlane - _camera->nearPlane) - 1.0f;
	//float w_new = 1.0f;

 // Calculate the values for the projection matrix
    //float x0 = 1.0f / (_camera->aspectRatio * _camera->tanHalfFov);
    //float y1 = 1.0f / _camera->tanHalfFov;
    //float z2 = -(_camera->farPlane + _camera->nearPlane) * _camera->rangeInv;
    //float t2 = -(2.0f * _camera->farPlane * _camera->nearPlane) * _camera->rangeInv;
    //float w2 = -1.0f;


    /*    // Oorthographic projection matrix
	| 2/x_max   0        0                     -1             |
	|    0  -2/y_max     0                      1             |
	|    0      0   2/(zFar-zNear)  (zNear+zFar)/(zNear-zFar) |
	|    0      0        0                      1             |
     */
	// TODO: fix this
    // Get the framebuffer width and height as we work in pixels
    _camera->windowWidth = _window->frameBufferWidth;//_window->windowWidth;
    _camera->windowHeight = _window->frameBufferHeight;//_window->windowHeight;
    _camera->fov = 45.0f;
    _camera->nearPlane = 0.01f;
    _camera->farPlane = 100.0f;
    _camera->aspectRatio =  _camera->windowWidth / _camera->windowHeight;
    _camera->tanHalfFov = tan(_camera->fov * 0.5f);
    _camera->rangeInv = 1.0f / (_camera->farPlane - _camera->nearPlane);

    float orthoWidth = 10.0f;
    float orthoHeight = orthoWidth / _camera->aspectRatio;
    float right = orthoWidth / 2;//5.0f;       //_camera->windowWidth; 
    float left = -orthoWidth / 2;//0.0f;
    float top = orthoHeight / 2;//5.0f;        //_camera->windowHeight;
    float bottom = -orthoHeight / 2;//0.0f;    //0.0f;

    // Set the elements of the projection matrix
    AF_Mat4 orth_projectionMatrix;
    orth_projectionMatrix.rows[0].x = 2/(right - left);
    orth_projectionMatrix.rows[0].y = 0.0f;
    orth_projectionMatrix.rows[0].z = 0.0f;
    orth_projectionMatrix.rows[0].w = 0.0f;
    
    orth_projectionMatrix.rows[1].x = 0.0f;
    orth_projectionMatrix.rows[1].y = 2/(top - bottom);
    orth_projectionMatrix.rows[1].z = 0.0f;
    orth_projectionMatrix.rows[1].w = 0.0f; 

    orth_projectionMatrix.rows[2].x = 0.0f;
    orth_projectionMatrix.rows[2].y = 0.0f;
    orth_projectionMatrix.rows[2].z = -2/(_camera->farPlane - _camera->nearPlane);
    orth_projectionMatrix.rows[2].w = 0.0f;

    orth_projectionMatrix.rows[3].x = 0;//-(right + left) / (right - left);
    orth_projectionMatrix.rows[3].y = 0;//-(top + bottom) / (top - bottom);
    orth_projectionMatrix.rows[3].z = 0;//-(_camera->farPlane + _camera->nearPlane)/(_camera->farPlane - _camera->nearPlane);
    orth_projectionMatrix.rows[3].w = 1.0f;

    return orth_projectionMatrix;
	
}


static inline AF_Vec3 AF_Camera_CalculateFront(float _yaw, float _pitch){
 // calculate the new Front vector
    float x = cos(AF_Math_Radians(_yaw)) * cos(AF_Math_Radians(_pitch));
    float y = sin(AF_Math_Radians(_pitch));
    float z = sin(AF_Math_Radians(_yaw)) * cos(AF_Math_Radians(_pitch));
    AF_Vec3 normalisedVec3 = {x, y, z};
    AF_Vec3 newFront = AFV3_NORMALIZE(normalisedVec3);

    return newFront;
}



#ifdef __cplusplus
}
#endif

#endif //AF_CCAMERA_H
