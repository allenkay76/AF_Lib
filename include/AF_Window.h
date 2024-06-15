#ifndef AF_WINDOW_H
#define AF_WINDOW_H
#include "AF_Lib_Define.h"

typedef struct {
    void* window;
} AF_Window;

void AFLib_CreateWindow(AF_Window* _window);
bool AFLib_UpdateWindow(AF_Window* _window);
void AFLib_TerminateWindow(AF_Window* _window);



#endif  // AF_WINDOW_H
