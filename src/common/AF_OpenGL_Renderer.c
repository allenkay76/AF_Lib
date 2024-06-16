#include "AF_Renderer.h"
#include <stdio.h>
#include "AF_Log.h"

const char* openglRendererFileTitle = "AF_OpenGL_Renderer:";
// Implementations
void AF_LIB_InitRenderer(void){
    AF_Log("%s Initialized\n", openglRendererFileTitle);

}


void AF_LIB_DisplayRenderer(void){
    //printf("OpenGL Display\n");
}

void AF_LIB_DestroyRenderer(void){
    AF_Log("%s Destroyed\n", openglRendererFileTitle);
}
