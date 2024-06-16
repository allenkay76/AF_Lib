#ifndef AF_WINDOW_H
#define AF_WINDOW_H
#include <stdint.h>
#include "AF_Lib_Define.h"
#include "AF_Input.h"


typedef struct {
    void* window;
    void* input;
    const char* title;
    uint16_t windowWidth;
    uint16_t windowHeight;
} AF_Window;

void AFLib_CreateWindow(AF_Window* _window);
bool AFLib_UpdateWindow(AF_Window* _window);
void AFLib_TerminateWindow(AF_Window* _window);



#endif  // AF_WINDOW_H
