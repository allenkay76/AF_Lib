#include "AF_Renderer.h"
#include <stdio.h>
#include "AF_Log.h"

const char* openglRendererFileTitle = "AF_OpenGL_Renderer:";
// Implementations
void AFLIB_InitRenderer(void){
    AFLibLog("%s Initialized\n", openglRendererFileTitle);

}


void AFLIB_DisplayRenderer(void){
    //printf("OpenGL Display\n");
}

void AFLIB_DestroyRenderer(void){
    AFLibLog("%s Destroyed\n", openglRendererFileTitle);
}
