#include "AF_Window.h"
#include <stdio.h>
#include "AF_Window_Cocoa.h"

// ------- Create OSX Window -------


// Implementation 
void AF_Lib_CreateWindow(void) {
    @autoreleasepool{
        [AF_Window_Cocoa CreateOSXWindow];
    }
}
