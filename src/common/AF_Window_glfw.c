/*
===============================================================================
AF_Window_glfw implementation

Implementation for AF_Window using GLFW
Calls GLFW library to handling window creation and input handling
===============================================================================
*/
#include "AF_Window.h"
#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "AF_Input.h"
#include "AF_Log.h"
#include <GL/glew.h>
#define GL_SILENCE_DEPRECATION

// ------- Create Platform Independent Window -------
// TODO: make this get passed into create window
const char* glfwWindowFileTitle = "AF_Window_GLFW:";


/*
====================
error_callback
General Error callback used by glfw
====================
*/
void error_callback(int error, const char* description)
{
    AF_Log_Error("%s %s %i\n", glfwWindowFileTitle, description, error);
}


/*
====================
key_callback
Key callback used by glfw
====================
*/
static void key_callback(GLFWwindow* _window, int key, int scancode, int action, int mods)
{
	// TODO: https://www.reddit.com/r/opengl/comments/i8lv8u/how_can_i_optimize_my_key_handling_and_make_it/
    if(scancode){}
    if(mods){}
    AF_Input* input = (AF_Input*)glfwGetWindowUserPointer(_window);

    if(action == GLFW_PRESS){
	// find the key and set it to pressed
	for(int i = 0; i < AF_INPUT_KEYS_MAPPED; i++){
		if(input->keys[i].code == key){
			input->keys[i].pressed = 1;
		}
	}
    }else if(action == GLFW_RELEASE){
	// find the key and set it to release
	for(int i = 0; i < AF_INPUT_KEYS_MAPPED; i++){
		if(input->keys[i].code == key){
			input->keys[i].pressed = 0;
		}
	}

    }
    // Retrieve the pointer to the AF_Input struct from the window user pointer
    // increment the buffer to position the next key, rollover if at the end of the array
     
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }
}

/*
====================
window_pos_callback
Move window callback
====================
*/
void window_pos_callback(GLFWwindow* _window, int _xpos, int _ypos){
    // if the window is moved, update the glviewport
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    //if(_xpos || _ypos){}
    glViewport(_xpos, _ypos, width, height);
}

/*
====================
framebuffer_size_callback
when the framebuffer size changes, update the glViewport
====================
*/
void framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
{
    if(_window){}
    glViewport(0, 0, _width, _height);
}



/*
====================
AF_Lib_CreateWindow
Create a window using GLFW
====================
*/
void AF_Lib_CreateWindow(AF_Window* _window) {
    if(!_window){
        printf("%s CreateWindow: _window is NULL\n", glfwWindowFileTitle);
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

    // set window move callpack
    glfwSetWindowPosCallback(glfwWindow, window_pos_callback);

    // Set the window size correctly, needed for OSX retina displays
    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);

}

/*
====================
AF_Window_Refresh
Refresh the window by updating the viewport size
====================
*/

void AF_Window_Refresh(AF_Window* _window){
    // When on osx retina displays we often need to use the framebuffer to actually set the gl viewport size.
    int width, height;
    glfwGetFramebufferSize((GLFWwindow*)_window->window, &width, &height);
    glViewport(0, 0, width, height);
}

/*
====================
AF_Lib_UpdateWindow
Update the window
====================
*/
BOOL AF_Lib_UpdateWindow(AF_Window* _window){
    // while
    if (glfwWindowShouldClose(_window->window))
    {
        // Close the window
        return FALSE;
    }
    
    /* Render here */

    /* Swap front and back buffers */
    glfwSwapBuffers(_window->window);

    /* Poll for and process events */
    glfwPollEvents();
    // return true (we are still running)
    return TRUE;
}


/*====================
AF_Lib_TerminateWindow
Destroy the window
====================
*/
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



