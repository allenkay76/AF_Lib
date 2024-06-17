#include "AF_Window.h"
#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "AF_Input.h"
#include "AF_Log.h"

//#include <glad/gl.h>
// ------- Create Platform Independent Window -------
const char* glfwWindowFileTitle = "AF_Window_GLFW:";


// forward declare
void error_callback(int error, const char* description)
{
    AF_Log_Error("%s %s %i\n", glfwWindowFileTitle, description, error);
}

static void key_callback(GLFWwindow* _window, int key, int scancode, int action, int mods)
{
    if(scancode){}
    if(mods){}

    // Retrieve the pointer to the AF_Input struct from the window user pointer
    AF_Input* state = (AF_Input*)glfwGetWindowUserPointer(_window);
    state->lastKeyCodePressed = key;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }
}

// Implementation 
void AF_Lib_CreateWindow(AF_Window* _window) {
    if(!_window){
        AF_Log_Error("%s CreateWindow: failed to create window\n", glfwWindowFileTitle);
        return;
    }

    AF_Log("%s Create Window\n", glfwWindowFileTitle);
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        // Initialization failed
        AF_Log_Error("%sCreateWindow: Failed to init glfw\n", glfwWindowFileTitle);
    }

    
    // If using openGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* glfwWindow = glfwCreateWindow(_window->windowWidth, _window->windowHeight, _window->title, NULL, NULL);
   
    
    if (!glfwWindow)
    {
        // Window or context creation failed
         AF_Log_Error("%s CreateWindow: Failed to create a window\n", glfwWindowFileTitle);
    }
    // assign the glfw window ptr to the struct passed in
     _window->window = glfwWindow;

    // make current context
    glfwMakeContextCurrent(glfwWindow);

    // Set the struct pointer as the user pointer of the window for input callback
    glfwSetWindowUserPointer(glfwWindow, _window->input);


    // Set callback
    glfwSetKeyCallback(glfwWindow, key_callback);
}

BOOL AF_Lib_UpdateWindow(AF_Window* _window){
    // while
    if (glfwWindowShouldClose(_window->window))
    {
        // Close the window
        return FALSE;
    }
    
    /* Render here */
    //glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(_window->window);

    /* Poll for and process events */
    glfwPollEvents();
    // return true (we are still running)
    return TRUE;
}


void AF_Lib_TerminateWindow(AF_Window* _window){
    // null check the struct
    if(!_window){
        AF_Log_Error("%s TerminateWindow: failed to destroy window, argment passed in a null AF_Window struct\n", glfwWindowFileTitle);
        return;
    }

    // Null check the window pointer
    if(!_window->window){
        AF_Log_Error("%s TerminateWindow: failed to create window, argment passed in a null window ptr\n", glfwWindowFileTitle);
        return;
    }

    AF_Log("%s TerminateWindow:\n", glfwWindowFileTitle);
     // Destory the wndow
    glfwDestroyWindow(_window->window);
    glfwTerminate();
}

