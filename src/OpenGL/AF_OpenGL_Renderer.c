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
#include "AF_Mat4.h"
#include <GL/glew.h>
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

// OpenGL errors
const char* invalidEnum = "INVALID_ENUM";
const char* invalidValue = "INVALID_VALUE";
const char* invalidOperation = "INVALID_OPERATION";
const char* stackOverflow = "STACK_OVERFLOW";
const char* stackUnderflow = "STACK_UNDERFLOW";
const char* outOfMemory = "OUT_OF_MEMORY";
const char* invalidFrameBufferOperation = "INVALID_FRAMEBUFFER_OPERATION";



/*
====================
AF_CheckGLError
Helper function for checking for GL errors
====================
*/
void AF_CheckGLError(const char* _message){    
    GLenum errorCode = GL_NO_ERROR;
    errorCode = glGetError();
    const char* errorMessage = "";
    if(errorMessage){}
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
	switch (errorCode)
        {
            case GL_INVALID_ENUM:                  errorMessage  = invalidEnum; break;
            case GL_INVALID_VALUE:                 errorMessage  = invalidValue; break;
            case GL_INVALID_OPERATION:             errorMessage  = invalidOperation; break;
            case GL_STACK_OVERFLOW:                errorMessage  = stackOverflow; break;
            case GL_STACK_UNDERFLOW:               errorMessage  = stackUnderflow; break;
            case GL_OUT_OF_MEMORY:                 errorMessage  = outOfMemory; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: errorMessage  = invalidFrameBufferOperation; break;
        }
    AF_Log_Error(_message,errorMessage);

    }
           //printf("\nGL Error: %i\n", error);
}

/*
====================
AF_Log_Mat4
Take a AF_Mat 4 and log it to the console.
====================
*/
void AF_Log_Mat4(AF_Mat4 _mat4){
	AF_Log("		Row 1: %f %f %f %f\n\
		Row 2: %f %f %f %f\n\
		Row 3: %f %f %f %f\n\
		Row 4: %f %f %f %f\n\n",
		_mat4.rows[0].x, 
		_mat4.rows[0].y,
		_mat4.rows[0].z,
		_mat4.rows[0].w,

		_mat4.rows[1].x,
		_mat4.rows[1].y,
		_mat4.rows[1].z,
		_mat4.rows[1].w,

		_mat4.rows[2].x,
		_mat4.rows[2].y,
		_mat4.rows[2].z,
		_mat4.rows[2].w,

		_mat4.rows[3].x,
		_mat4.rows[3].y,
		_mat4.rows[3].z,
		_mat4.rows[3].w);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int AF_Renderer_LoadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);  

    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1){
            format = GL_RED;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
        }
        else if (nrComponents == 4){
            format = GL_RGBA;
        }
            

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Use these filters for normal textures
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Use these filters for pixel art sprites.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);
    }
    else
    {
	AF_Log_Error("Texture failed to load at path %s\n",path);
        stbi_image_free(data);
    }

    return textureID;
}

void AF_Renderer_SetTexture(const unsigned int _shaderID, const char* _shaderVarName, int _textureID){
    glUseProgram(_shaderID); // Bind the shader program
    glUniform1i(glGetUniformLocation(_shaderID, _shaderVarName), _textureID); // Tell the shader to set the "Diffuse_Texture" variable to use texture id 0
    glUseProgram(0);
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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
    
    /**/

    //set the glViewport and the perspective
    //glViewport(_window->windowXPos, _window->windowYPos, _window->windowWidth, _window->windowHeight);

        // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
void AF_LIB_DisplayRenderer(AF_Window* _window, AF_CCamera* _camera, AF_MeshData* _meshList, AF_CTransform3D* _meshTransforms,  AF_Sprite* _spritesList){
    AF_CheckGLError( "Error at start of Rendering OpenGL! \n");
    glClearColor(_camera->backgroundColor.x, _camera->backgroundColor.y, _camera->backgroundColor.z, _camera->backgroundColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable transparent blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // if in 2d mode, disable depth testing
    glDisable(GL_DEPTH_TEST);

    _window->title = _window->title;
    _camera->transform->pos = _camera->transform->pos;
    // Get the width and height from the frambuffer instead of the original set window size as open gl works in pixels
    _camera->windowWidth = _window->frameBufferWidth;//_window->windowWidth;
    _camera->windowHeight = _window->frameBufferHeight;//_window->windowHeight;


    // update the game camera with the window width
   
    // update camera vectors
    //TODO: put in switch if using mouse look to calculate front based on yaw and pitch
    AF_Vec3 front = _camera->cameraFront;//AF_Camera_CalculateFront(yaw, pitch);

    // calculate Right
    AF_Vec3 right = AFV3_NORMALIZE(AFV3_CROSS(front, _camera->cameraWorldUp));
	
    // calculate up
    AF_Vec3 up = AFV3_NORMALIZE(AFV3_CROSS(right, front));
	
    // Calculate view matrix:vs
    //
    AF_Mat4 viewMatrix = AF_Math_Lookat(_camera->transform->pos, AFV3_ADD(_camera->transform->pos,front), up);
    _camera->viewMatrix = viewMatrix;

    // Calculate projection matrix
    //if(_camera->orthographic == TRUE){
    _camera->projectionMatrix = AF_Camera_GetOrthographicProjectionMatrix(_window, _camera);
    //}else{
	//AF_Log("OpenGL_Renderer: NO Projection Matrix setup \n");
    //}

    _meshList->numMeshes = _meshList->numMeshes;


    // Set the winding order to clockwise
    //glFrontFace(GL_CW); // Clockwise winding order
    //glFrontFace(GL_CCW); // Counterclockwise winding order (default)


    // Enable face culling
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);  // Cull back faces
    //glDisable(GL_CULL_FACE);

    glUseProgram(_meshList->materials[0].shaderID); 
    AF_CheckGLError( "Error at useProgram Rendering OpenGL! \n");
    GLint textureUniformLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "image");
    GLint projLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "projection");
    GLint viewLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "view");
    GLint modelLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "model");
    
    // TODO: this is sprite specific, so fix this.
    // Get the shader variable locations
    GLint spriteSizeLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "spriteSize");
    GLint spriteFrameLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "spriteFrame");
       

    // Send camrea data to shader
    // Projection Matrix
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, (float*)&_camera->projectionMatrix.rows[0]);

    // View Matrix
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (float*)&_camera->viewMatrix.rows[0]);
	

    
    for(uint32_t i = 0; i < _meshList->numMeshes; i++){
        // Draw mesh
        //AF_Log("AF_OpenGL_Renderer:\nRendering mesh %i: %i verts, %i indices\n", i, _meshList->meshes[i].vertexCount,_meshList->meshes[i].indexCount);
        
	// TODO: put into forloop to upate shader with all model transforms
	
	// world transformation
	if(_meshTransforms == NULL){
		AF_Log_Error("AF_OpenGL_Renderer::Render: Null mesh transforms\n");
		return;
	}
	// convert to vec4 for model matrix
	AF_Vec4 modelPos = {_meshTransforms[i].pos.x, _meshTransforms[i].pos.y, _meshTransforms[i].pos.z, 1.0f};
	AF_Vec4 modelRot = {_meshTransforms[i].rot.x, _meshTransforms[i].rot.y, _meshTransforms[i].rot.z, 1.0f};
	AF_Vec4 modelScale = {_meshTransforms[i].scale.x, _meshTransforms[i].scale.y, _meshTransforms[i].scale.z, 1.0f};

	
	// apply rotation to postion and scaled matrix
	AF_Mat4 rotatedMatrix = AFM4_ROTATE_V4(AFM4_IDENTITY(), modelRot);//AFM4_DOT_M4( rotatedMatrix, scaleMatrix);
									  
	// Apply scale
	AF_Mat4 scaleMatrix = AFM4_SCALE_V4(AFM4_IDENTITY(), modelScale); 

	// apply rotation to postion and scaled matrix
	AF_Mat4 rsMat = AFM4_DOT_M4(rotatedMatrix, scaleMatrix);
	
	// Construct the final model matrix with translation using row-major order
	AF_Mat4 modelMatrix = {{
	    {rsMat.rows[0].x, rsMat.rows[0].y, rsMat.rows[0].z, modelPos.x},
	    {rsMat.rows[1].x, rsMat.rows[1].y, rsMat.rows[1].z, modelPos.y},
	    {rsMat.rows[2].x, rsMat.rows[2].y, rsMat.rows[2].z, modelPos.z},
	    {rsMat.rows[3].x, rsMat.rows[3].y, rsMat.rows[3].z, 1.0f}
	}};
	
	//AF_Log_Mat4(modelMatrix);	
	// Set model matrix Mat4 for shader
	glUniformMatrix4fv(modelLocation, 1, GL_TRUE, (float*)&modelMatrix.rows[0]);
	
	
	// Tell the shader about the sprite position
        if (spriteSizeLocation != -1) {
	    GLfloat spriteSize[2] = {_spritesList[i].size.x, _spritesList[i].size.y};
            glUniform2fv(spriteSizeLocation, 1, spriteSize);
        }

        // Update the sprite position
        if (spriteFrameLocation != -1) {
            GLfloat spriteFrame[2] = {_spritesList[i].currentFrame, _spritesList[i].pos.y};
            glUniform2fv(spriteFrameLocation, 1, spriteFrame);
        }
	
	// Set the texture for the shader
	glUniform1i(textureUniformLocation,0);// _meshList->materials[0].textureID); 
	glActiveTexture(GL_TEXTURE0);
	// TODO implement binding the actual texture
	//unsigned int diffuseTexture = _mesh.material.diffuseTexture;
	glBindTexture(GL_TEXTURE_2D, _meshList->materials[i].textureID);
	AF_CheckGLError("Error blBindTexture diffuse ");

        
        
        // draw mesh
        glBindVertexArray(_meshList->vao);
        AF_CheckGLError( "Error bind vao Rendering OpenGL! \n");
        //---------------Send command to Graphics API to Draw Triangles------------
        
        glDrawElements(GL_TRIANGLES, (unsigned int)_meshList->meshes[i].indexCount, GL_UNSIGNED_INT, 0);
        
        AF_CheckGLError( "Error drawElements Rendering OpenGL! \n");
        
        glBindVertexArray(0);
        AF_CheckGLError( "Error bindvertexarray(0) Rendering OpenGL! \n");
	
	// Unbind textures
    	//unbind diffuse
    	glActiveTexture(GL_TEXTURE0);
    	glBindTexture(GL_TEXTURE_2D, 0);

    }
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
    glDeleteProgram(_meshList->materials[0].shaderID);
    
        //glDeleteTexture(_meshList->materials[0].textureID);
    AF_CheckGLError( "Error Destroying Renderer OpenGL! \n");
}

