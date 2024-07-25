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
AF_Log_Mat4
Take a AF_Mat 4 and log it to the console.
====================
*/
void AF_Log_Mat4(AF_Mat4 _mat4){
	AF_Log("	Row 1: %f %f %f %f\n\
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
AF_Renderer_DisplaySprite
Display the sprites renderer
====================
*/
void AF_Renderer_DisplaySprite(AF_MeshData* _meshList, AF_Sprite* _spritesList, int _frame){
 	AF_CheckGLError( "Error at start of Rendering sprite OpenGL! \n");
	glUseProgram(_meshList->materials[0].shaderID); 
	// Get the shader variable locations
	GLint spriteSizeLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "spriteSize");
	GLint spriteFrameLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "spriteFrame");
	// Set the frame
	
	// For each sprite mesh, update the sprite sheet position by the frame
	for(uint32_t i = 0; i < _meshList->numMeshes; i++){
		glUniform1i(spriteSizeLocation, _spritesList[i].size.x);

		// update the sprite Pos
		GLfloat spriteFrame[2] = {_frame, _spritesList[i].pos.y};
		glUniform2fv(spriteFrameLocation, 1, spriteFrame);

	}
 	AF_CheckGLError( "Error at end of Rendering sprite OpenGL! \n");
}


/*
====================
AF_LIB_DisplayRenderer
Display the renderer
====================
*/
void AF_LIB_DisplayRenderer(AF_Window* _window, AF_CCamera* _camera, AF_MeshData* _meshList, AF_CTransform3D* _meshTransforms){
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
    _camera->windowWidth = _window->windowWidth;
    _camera->windowHeight = _window->windowHeight;


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
    
    for(uint32_t i = 0; i < _meshList->numMeshes; i++){
        // Draw mesh
        //AF_Log("AF_OpenGL_Renderer:\nRendering mesh %i: %i verts, %i indices\n", i, _meshList->meshes[i].vertexCount,_meshList->meshes[i].indexCount);
        
        // Send camrea data to shader
        // Projection Matrix
	GLint projLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "projection");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, (float*)&_camera->projectionMatrix.rows[0]);

	// View Matrix
	GLint viewLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (float*)&_camera->viewMatrix.rows[0]);
	
	// TODO: put into forloop to upate shader with all model transforms
	
	// world transformation
	if(_meshTransforms == NULL){
		AF_Log_Error("AF_OpenGL_Renderer::Render: Null mesh transforms\n");
		return;
	}
	// convert to vec4 for model matrix
	AF_Vec4 modelPos = {_meshTransforms[i].pos.x, _meshTransforms[i].pos.y, _meshTransforms[i].pos.z, 1.0f};
	// Create the model matrix in row oder format
	AF_Mat4 modelMatrix = {{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
    		{0.0f, 0.0f, 1.0f, 0.0f},
    		modelPos			// Row order position
	}};
	
	// Set model matrix Mat4 for shader
	GLint modelLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, (float*)&modelMatrix.rows[0]);
	
		
        // bind diffuse map
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, diffuseMap);

	//--------------Bind Texture data----------------------
	//TODO: load diffuse texture to a piece of memory
        //bind diffuse texture
        //if(_mesh.material.diffuseTexture > 0){
	       //bind the diffuse texture
	       //// bind diffuse map
	int uniformLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "image");
	//AF_Log("UniformLocation: %i\n",uniformLocation);
	glUniform1i(uniformLocation,0);// _meshList->materials[0].textureID); 
	glActiveTexture(GL_TEXTURE0);
	// TODO implement binding the actual texture
	//unsigned int diffuseTexture = _mesh.material.diffuseTexture;
	glBindTexture(GL_TEXTURE_2D, _meshList->materials[0].textureID);
	AF_CheckGLError("Error blBindTexture diffuse ");
       // }


        //GLint spriteSizeLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "spriteSize");
	//GLint spriteFrameLocation = glGetUniformLocation(_meshList->materials[0].shaderID, "spriteFrame");

	
	// Set the frame
	//GLfloat spriteFrame[2] = {1.0f, 1.0f};
	//glUniform2fv(spriteFrameLocation, 1, spriteFrame);

	// For each sprite mesh, update the sprite sheet position by the frame
	//glUniform1i(spriteSizeLocation, 4);

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
        
        glDrawElements(GL_TRIANGLES, (unsigned int)_meshList->meshes[0].indexCount, GL_UNSIGNED_INT, 0);
        
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

