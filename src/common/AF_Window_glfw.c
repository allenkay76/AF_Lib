#include "AF_Window.h"
#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "AF_Input.h"
//#include <glad/gl.h>
// ------- Create Platform Independent Window -------



// forward declare
void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s %i\n", description, error);
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
void AFLib_CreateWindow(AF_Window* _window) {
    if(!_window){
        printf("AFLib_CreateWindow: failed to create window, argment passed in a null window\n");
        return;
    }

    printf("Create glfw window\n");
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        // Initialization failed
        printf("Failed to init glfw in Create AF_Window glfw\n");
    }

    

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* glfwWindow = glfwCreateWindow(_window->windowWidth, _window->windowHeight, _window->title, NULL, NULL);
   
    
    if (!glfwWindow)
    {
        // Window or context creation failed
         printf("Failed to create a window in Create glfw window glfw\n");
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

bool AFLib_UpdateWindow(AF_Window* _window){
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


void AFLib_TerminateWindow(AF_Window* _window){
    // null check the struct
    if(!_window){
        printf("AFLib_CreateWindow: failed to destroy window, argment passed in a null AF_Window struct\n");
        return;
    }

    // Null check the window pointer
    if(!_window->window){
        printf("AFLib_CreateWindow: failed to create window, argment passed in a null window ptr\n");
        return;
    }

    printf("Terminate GLFW Window\n");
     // Destory the wndow
    glfwDestroyWindow(_window->window);
    glfwTerminate();
}

