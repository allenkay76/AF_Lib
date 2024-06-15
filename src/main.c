#include <stdio.h>
#include "AF_Window.h"
#include "AF_Input.h"
#include "AF_Renderer.h"

// Forward declare of c function
int main(void);

int main(void) {
    printf("ENTRY POINT: AF_Lib\n");

    
    // Input
    AF_Input gameInput =  {0,0,0.0f, 0.0f};

   // Create the window
    AF_Window gameWindow;
    AFLib_CreateWindow(&gameWindow, &gameInput);

    // Create the renderer
    AFLIB_InitRenderer();

    
    // update the window
    while(AFLib_UpdateWindow(&gameWindow)){

        // Display the renderer
        AFLIB_DisplayRenderer();

        // Check for escape key pressed
        if(gameInput.lastKeyCodePressed == 256){
            printf("ESC pressed \n");
            break;
        }
    }

    // Destroy the renderer
    AFLIB_DestroyRenderer();

    // Destroy the window
    AFLib_TerminateWindow(&gameWindow);
    return 0;
}

