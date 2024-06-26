/*
===============================================================================
AF_OpenGL_Renderer Implementation

Implementation of the AF_LIB rendering functions
This implementation is for OpenGL
===============================================================================
*/
#include "AF_Renderer.h"
#include <stdio.h>
#include "AF_Log.h"
#include "AF_Vec3.h"
#include <GL/glew.h>
#define GL_SILENCE_DEPRECATION

// string to use in logging
const char* openglRendererFileTitle = "AF_OpenGL_Renderer:";

/*
====================
AF_CheckGLError
Helper function for checking for GL errors
====================
*/
void AF_CheckGLError(const char* _message){
    AF_Log(_message);
    
    GLenum error = GL_NO_ERROR;
    error = glGetError();
    if (error != GL_NO_ERROR) {
        AF_Log_Error("%s %s\n", error, _message);
    }
    
}

/*
====================
AF_LIB_InitRenderer
Init OpenGL
====================
*/
int AF_LIB_InitRenderer(AF_Window* _window){
    int success = 1;
    AF_Log("%s Initialized %s\n", openglRendererFileTitle, _window->title);
    //Initialize GLEW
    glewExperimental = GL_TRUE; 
    GLenum glewError = glewInit();
    if( glewError != GLEW_OK )
    {
        AF_Log_Error( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
    }

    //Use Vsync
    /*
    if( SDL_GL_SetSwapInterval( 1 ) < 0 )
    {
        AF_Log_Error( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
        success = 0;
    }*/

    //Initialize OpenGL
    /*
    if( !initGL() )
    {
        AF_Log_Error( "Unable to initialize OpenGL!\n" );
        success = 0;
    }*/

    //set the glViewport and the perspective
    //glViewport(0, 0, _window->windowWidth, _window->windowHeight);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    //AF_CheckGLError("SLDGameRenderer::Initialise:: finishing up init: ");
    return success;
} 

/*
====================
AF_LIB_InitMeshBuffers
Init the mesh buffers for OpenGL
====================
*/
void AF_LIB_InitMeshBuffers(AF_MeshData* _meshList){    
    int vertexBufferSize = 0;
    //int indexBufferSize = 0;
    for(int i = 0; i < _meshList->numMeshes; i++){
        // count up the amount of memory this should take i.e. vertex structs * size of a float*3
        vertexBufferSize += _meshList->meshes[i].vertexCount * ((sizeof(float))*3);
        //indexBufferSize += _meshList->meshes[i].indexCount * (sizeof(float));
    }

    
    GLuint gVAO, gVBO;//, gIBO;
    glGenVertexArrays(1, &gVAO);
    glGenBuffers(1, &gVBO);
    //glGenBuffers(1, &gIBO);

    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize , _meshList->meshes->vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(gVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    _meshList->vao = gVAO;
    _meshList->vbo = gVBO;
    //_meshList->meshes->ibo = gIBO;
    // Bind the IBO and set the buffer data
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, _meshList->meshes->indices, GL_STATIC_DRAW);
    
}

/*
====================
AF_LIB_DisplayRenderer
Display the renderer
====================
*/
void AF_LIB_DisplayRenderer(AF_Window* _window, AF_CCamera* _camera, AF_MeshData* _meshList){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //printf("OpenGL Display\n");
    _window->title = _window->title;
    _camera->transform->pos = _camera->transform->pos;
    _meshList->numMeshes = _meshList->numMeshes;
    for(int i = 0; i < _meshList->numMeshes; i++){
        // Draw mesh
        AF_Log("AF_OpenGL_Renderer:\nRendering mesh %i: %i verts, %i indices\n", i, _meshList->meshes[i].vertexCount,_meshList->meshes[i].indexCount);
        
        
        // view/projection transformations
        //projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 view = camera.GetViewMatrix();
        //lightingShader.setMat4("projection", projection);
        //lightingShader.setMat4("view", view);

        // world transformation
        //glm::mat4 model = glm::mat4(1.0f);
        //lightingShader.setMat4("model", model);

        // bind diffuse map
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, diffuseMap);

        glBindVertexArray(_meshList->vao);
        //glDrawElements(GL_TRIANGLES, _meshList->meshes[i].indexCount, GL_UNSIGNED_INT, 0

        // calculate the model matrix for each object and pass it to shader before drawing
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, cubePositions[i]);
        //float angle = 20.0f * i;
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    } 

        
}

/*
====================
AF_LIB_DestroyRenderer
Destroy the renderer
====================
*/
void AF_LIB_DestroyRenderer(void){
    AF_Log("%s Destroyed\n", openglRendererFileTitle);

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //glDeleteVertexArrays(1, &cubeVAO);
    //glDeleteBuffers(1, &VBO);
}
