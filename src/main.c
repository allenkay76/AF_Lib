#include <stdio.h>
#include "AF_Window.h"
#include "AF_Renderer.h"



// Forward declare of c function
int main(void);

int main(void) {
    printf("ENTRY POINT: AF_Lib\n");

    
   // Create the window
    AF_Window gameWindow;
    AFLib_CreateWindow(&gameWindow);

    // Create the renderer
    AFLIB_InitRenderer();

    // update the window
    while(AFLib_UpdateWindow(&gameWindow)){

        // Display the renderer
        AFLIB_DisplayRenderer();
    }

    // Destroy the renderer
    AFLIB_DestroyRenderer();

    // Destroy the window
    AFLib_TerminateWindow(&gameWindow);
    return 0;
}

