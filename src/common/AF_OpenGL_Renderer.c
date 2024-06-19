#include "AF_Renderer.h"
#include <stdio.h>
#include "AF_Log.h"
#include "AF_Vec3.h"

const char* openglRendererFileTitle = "AF_OpenGL_Renderer:";
// Implementations
void AF_LIB_InitRenderer(AF_Window* _window){
    AF_Log("%s Initialized %s\n", openglRendererFileTitle, _window->title);
} 


void AF_LIB_DisplayRenderer(AF_Window* _window, AF_CCamera* _camera, AF_MeshData* _meshList){
    //printf("OpenGL Display\n");
    _window->title = _window->title;
    _camera->transform->pos = _camera->transform->pos;
    _meshList->numMeshes = _meshList->numMeshes;
    for(int i = 0; i < _meshList->numMeshes; i++){
        // Draw mesh
        AF_Log("AF_OpenGL_Renderer:\nRendering mesh %i: %i verts, %i indices\n", i, _meshList->meshes[i].vertexCount,_meshList->meshes[i].indexCount);
    } 
}

void AF_LIB_DestroyRenderer(void){
    AF_Log("%s Destroyed\n", openglRendererFileTitle);
}
