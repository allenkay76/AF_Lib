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

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float vertices2[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

AF_Vertex vertices[4] = {
    { {0.5f,  0.5f, 0.0f}, {0.5f,  0.5f, 0.0f}, {0.5f,  0.5f} },
    { {0.5f, -0.5f, 0.0f}, {0.5f,  0.5f, 0.0f}, {0.5f,  0.5f} },
    { {-0.5f, -0.5f, 0.0f}, {0.5f,  0.5f, 0.0f}, {0.5f,  0.5f} },
    { {-0.5f,  0.5f, 0.0f}, {0.5f,  0.5f, 0.0f}, {0.5f,  0.5f} }
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

/*
====================
AF_CheckGLError
Helper function for checking for GL errors
====================
*/
void AF_CheckGLError(const char* _message){    
    GLenum error = GL_NO_ERROR;
    error = glGetError();
    if (error != GL_NO_ERROR) {
       
        // write
        AF_Log_Error(_message);
        printf("\nGL Error: %i\n", error);

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
    
     //Initialize clear color
    glClearColor(1.0f, 1.0f, 1.0f, 1.f );
    
    /**/

    //set the glViewport and the perspective
    glViewport(0, 0, _window->windowWidth, _window->windowHeight);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    AF_CheckGLError( "Error initializing OpenGL! \n");
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

    if (_meshList->numMeshes == 0) {
    AF_Log_Error("No meshes to draw!\n");
    return;
    }

    AF_Mesh* mesh = &_meshList->meshes[0];
    if (mesh->indexCount == 0) {
        AF_Log_Error("Mesh has no indices!\n");
        return;
    }

    if (!_meshList->meshes->vertices || !_meshList->meshes->indices) {
        AF_Log_Error("Invalid vertex or index data!\n");
        return;
    }

    int vertexBufferSize = _meshList->numMeshes * (mesh->vertexCount * sizeof(AF_Vertex));
    //AF_Log("Init GL Buffers for vertex buffer size of: %i\n",vertexBufferSize);
    /**/
    
    GLuint gVAO, gVBO, gEBO;
    glGenVertexArrays(1, &gVAO);
    glGenBuffers(1, &gVBO);
    glGenBuffers(1, &gEBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
    glBindVertexArray(gVAO);

    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    // our buffer needs to be 8 floats (3*pos, 3*normal, 2*tex)
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, mesh->vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the IBO and set the buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(unsigned int), &_meshList->meshes[0].indices[0], GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Stride is 8 floats wide, 3*pos, 3*normal, 2*tex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AF_Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AF_Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AF_Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    /**/

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    _meshList->vao = gVAO;
    _meshList->vbo = gVBO;
    _meshList->ibo = gEBO;
    // Bind the IBO and set the buffer data
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, _meshList->meshes->indices, GL_STATIC_DRAW);
    AF_CheckGLError( "Error InitMesh Buffers for OpenGL! \n");
}

/*
====================
AF_LIB_DisplayRenderer
Display the renderer
====================
*/
void AF_LIB_DisplayRenderer(AF_Window* _window, AF_CCamera* _camera, AF_MeshData* _meshList){
    AF_CheckGLError( "Error at start of Rendering OpenGL! \n");
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //printf("OpenGL Display\n");
    _window->title = _window->title;
    _camera->transform.pos = _camera->transform.pos;
    _meshList->numMeshes = _meshList->numMeshes;


    // Set the winding order to clockwise
    //glFrontFace(GL_CW); // Clockwise winding order
    //glFrontFace(GL_CCW); // Counterclockwise winding order (default)


    // Enable face culling
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);  // Cull back faces
    //glDisable(GL_CULL_FACE);

    glUseProgram(_meshList->shaderID); 
    AF_CheckGLError( "Error at useProgram Rendering OpenGL! \n");
    
    //for(uint32_t i = 0; i < _meshList->numMeshes; i++){
        // Draw mesh
        //AF_Log("AF_OpenGL_Renderer:\nRendering mesh %i: %i verts, %i indices\n", i, _meshList->meshes[i].vertexCount,_meshList->meshes[i].indexCount);
        
        
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

        
        //glDrawElements(GL_TRIANGLES, _meshList->meshes[i].indexCount, GL_UNSIGNED_INT, 0

        // calculate the model matrix for each object and pass it to shader before drawing
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, cubePositions[i]);
        //float angle = 20.0f * i;
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        //glDrawArrays(GL_TRIANGLES, 0, 36);

        
        
        // draw mesh
        glBindVertexArray(_meshList->vao);
        AF_CheckGLError( "Error bind vao Rendering OpenGL! \n");
        //---------------Send command to Graphics API to Draw Triangles------------
        //glDrawElements(GL_TRIANGLES, (unsigned int)_meshList->meshes[0].indexCount, GL_UNSIGNED_INT, NULL);
        
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //AF_CheckGLError( "Error drawTriangles Rendering OpenGL! \n");
        glDrawElements(GL_TRIANGLES, (unsigned int)_meshList->meshes[0].indexCount, GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        //AF_Mesh* mesh = &_meshList->meshes[0];
        //AF_Log("Mesh: %i\n",mesh->indexCount);
        //glDrawElements(GL_TRIANGLES, (unsigned int)_meshList->meshes[0].indexCount, GL_UNSIGNED_INT, 0);
        
       AF_CheckGLError( "Error drawElements Rendering OpenGL! \n");
        
        glBindVertexArray(0);
        AF_CheckGLError( "Error bindvertexarray(0) Rendering OpenGL! \n");
    //}
    AF_CheckGLError( "Error at end Rendering OpenGL! \n");
}

/*
====================
AF_LIB_DestroyRenderer
Destroy the renderer
====================
*/
void AF_LIB_DestroyRenderer(AF_MeshData* _meshList){
    AF_Log("%s Destroyed\n", openglRendererFileTitle);

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &_meshList->vao);
    glDeleteBuffers(1, &_meshList->vbo);
    glDeleteBuffers(1, &_meshList->ibo);
    glDeleteProgram(_meshList->shaderID);
    AF_CheckGLError( "Error Destroying Renderer OpenGL! \n");
}

