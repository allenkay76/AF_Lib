#include <stdio.h>
#include <stdint.h>
#include "AF_Window.h"
#include "AF_Input.h"
#include "AF_Renderer.h"

// Forward declare of c function
int main(void);

const char * windowTitle = "AF_Lib";
const uint16_t windowWidth = 1280;
const uint16_t windowHeight = 720;

int main(void) {
    printf("ENTRY POINT: AF_Lib\n");

    
    // Input
    AF_Input gameInput =  {0,0,0.0f, 0.0f};

   // Create the window
    AF_Window gameWindow = {0, &gameInput, windowTitle, windowWidth, windowHeight};
    AFLib_CreateWindow(&gameWindow);

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

