#ifndef AF_WINDOW_H
#define AF_WINDOW_H
#include <stdint.h>
#include "AF_Lib_Define.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* window;           // Pointer to the window object (implementation specific)
    void* input;            // Pointer to the input handling object (implementation specific)
    const char* title;      // Title of the window
    uint16_t windowWidth;   // Width of the window
    uint16_t windowHeight;  // Height of the window
} AF_Window;

/// @brief Creates a window with the specified parameters
/// @param _window  Pointer to the window object that will be created (platform speficic)
void AFLib_CreateWindow(AF_Window* _window);

/// @brief Updates the window, called once per frame
/// @param _window  Pointer to the window struct containing the window object and other window data
/// @return 
bool AFLib_UpdateWindow(AF_Window* _window);

/// @brief Terminates the window and releases all resources
/// @param _window  pointer to the window struct containing the window object and other window data
void AFLib_TerminateWindow(AF_Window* _window);

#ifdef __cplusplus
}
#endif

#endif  // AF_WINDOW_H
