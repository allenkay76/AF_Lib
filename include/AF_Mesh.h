/*
===============================================================================
AF_Mesh_H

Header only Mesh loading
functions to load meshes, creating memory on the heap based on the size of the mesh

===============================================================================
*/
#ifndef AF_MESH_H
#define AF_MESH_H
#include "AF_Vertex.h"
// TODO: get rid of use of stb lib
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AF_Util.h"
#include "AF_Log.h"
#include "AF_Material.h"

#ifdef __cplusplus
extern "C" {
#endif  

#define AF_MESH_FILE_TITLE "AF_Mesh: "

// Mesh Struct
typedef struct {
    BOOL has;
    BOOL enabled;
    AF_Vertex* vertices;
    int vertexCount;
    unsigned int* indices;
    int indexCount;
    uint32_t vao;
    uint32_t vbo;
    uint32_t ibo;
    AF_Material material;
} AF_Mesh;

/*
====================
AF_Mesh_ZERO
Function used to create an empty mesh component
====================
*/
static inline AF_Mesh AF_Mesh_ZERO(void){
    AF_Mesh returnMesh = {
	.has = false,
	.enabled = false,
	.vertices = NULL,
	.vertexCount = 0,
	.indices = NULL,
	.indexCount = 0,
	.vao = 0,
	.vbo = 0,
	.ibo = 0,
	.material = {0,0}
    };
    return returnMesh;
}

/*
====================
AF_Mesh_ADD
Function used to Add the component
====================
*/
static inline AF_Mesh AF_Mesh_ADD(void){
    AF_Mesh returnMesh = {
	.has = true,
	.enabled = true,
	.vertices = NULL,
	.vertexCount = 0,
	.indices = NULL,
	.indexCount = 0,
	.vao = 0,
	.vbo = 0,
	.ibo = 0,
	.material = {0,0}
    };
    return returnMesh;
}


/*
====================
AF_Mesh_GetVec2FromString
Take in a char array and return the float values 
Extract and return the first two float values found
Used for extracting things like tex coords out of a .obj
====================
*/
static inline AF_Vec2 AF_Mesh_GetVec2FromString(char* _buffer){ //, uint16_t _size){
    AF_Vec2 returnVec2 = {0.0f, 0.0f};
    char* token = strtok(_buffer, " ");
    token = strtok(NULL, " ");
    if(token != NULL){
        float num1 = strtof(token, NULL);
        token = strtok(NULL, " ");
        float num2 = strtof(token, NULL);
        //AF_Log("Extracted Vec2 float %f %f \n", num1, num2);
        
        returnVec2.x = num1;
        returnVec2.y = num2;
    }
    // search the char buffer for the first two number characters and convet it to a vec2
   
    return returnVec2;
}

/*
====================
AF_Mesh_GetVec3FromString
Take in a char array and return the float values 
Extract and return the first 3 float values
Used for things like position values out of a .obj
====================
*/
static inline AF_Vec3 AF_Mesh_GetVec3FromString(char* _buffer){ //, uint16_t _size){
    AF_Vec3 returnVec3 = {0.0f, 0.0f, 0.0f};
    char* token = strtok(_buffer, " ");
    token = strtok(NULL, " ");
    if(token != NULL){
        float num1 = strtof(token, NULL);
        token = strtok(NULL, " ");
        float num2 = strtof(token, NULL);
        token = strtok(NULL, " ");
        float num3 = strtof(token, NULL);
        //AF_Log("Extracted Vec3 float %f %f %f \n", num1, num2, num3);
        
        returnVec3.x = num1;
        returnVec3.y = num2;
        returnVec3.z = num3;
    }
    // search the char buffer for the first two number characters and convet it to a vec2
   
    return returnVec3;
}

/*
====================
AF_Mesh_GetOBJAttribSize
Read a file, ideally in .obj format
extract each line, and determine how many verticies and indicies are in the 3d model
return a copy of a mesh struct with the verticies and indicies count values assigned. 
DOES NOT load the actual verticies or indices or create new memory on the heap.
====================
*/
static inline AF_Mesh AF_Mesh_GetOBJAttribSize(FILE* _file){
    AF_Mesh mesh = AF_Mesh_ZERO();
    if(_file == NULL){
        AF_Log_Error("%s Failed to open file to GetOBJAttribSize %s\n", AF_MESH_FILE_TITLE);
        return mesh;
    }

        // read the file and count
        // num of "v" verticies found 
        // num of "vt" texture coordsfound
        // num of "vn" normal vectors found
    char fileBuffer[1024] ; // Buffer for reading the file
    
    // read the file
    while(!feof(_file)){
        
         if(fgets(fileBuffer, 1024, _file) != NULL) {
        // print the return value (aka string read in) to terminal
            //AF_Vertex vertex ;
            if(fileBuffer[0] == 'v' && fileBuffer[1] == ' '){
                // vertex
                //AF_Vec3 vertPos = AF_Mesh_GetVec3FromString(fileBuffer);
                //vertex.position = vertPos;
                mesh.vertexCount++;
                continue;
            }
            if(fileBuffer[0] == 'f'){
                // face / indices
                // add 4 faces to the index count
                // search the first element of a new face token and store the value

                // cound the indicies
                char *p = strtok(fileBuffer, " ");
                while(p != NULL) {
                    if((strcmp(p,"f"))){
                        mesh.indexCount++;
                    }
                    //printf("%s\n", p);
                    // Move the tokens along
                    p = strtok(NULL, " ");
                }
                continue;
            }
            if(fileBuffer[0] == 'v' && fileBuffer[1] == 't'){
                // texture coordinate
                continue;
            }
            if(fileBuffer[0] == 'v' && fileBuffer[1] == 'n'){
                // normal
                continue;
            }
        }
    }
    // Move back to the beginning of the file using fseek and rewind
    fseek(_file, 0L, SEEK_SET);
    rewind(_file);
    
    return mesh;
}

/*
====================
AF_Mesh_Load_Data
Read a file, and perform needed operations to extract the data that hopefully is .obj format
This function relies on taking in a mesh object that already has the number of verticies and indicies assigned to a AF_Mesh struct
Function then reads the file data, creating memory on the heap to store the verticies and indicies.
Assigns the heap pointer value into the struct.
TODO: Make this utilise a memory manager like AF_Memory to ensure it allocates memory from pre-allocated game memory.
Don't trust the OS virtual memory allocation ;)
====================
*/
static inline AF_Mesh AF_Mesh_Load_Data(FILE* _file, AF_Mesh _mesh){
    int verticesCount = 0;//_mesh.vertexCount;
    int indicesCount = 0;//_mesh.indexCount;
    int texCoordsCount = 0; 
    char fileBuffer[1024] ; // Buffer for reading the file

    // Create a new AF_Struct, that holds the pointers to the heap allocated verticies and indices data
    AF_Mesh returnMesh = {
	    		0,
			0,
                        (AF_Vertex*)malloc(sizeof(AF_Vertex) * _mesh.vertexCount), 
                        _mesh.vertexCount,
                        (unsigned int*)malloc(sizeof(int) * _mesh.indexCount),
                        _mesh.indexCount,
			0,
			0,
			0,
			{0,0}
                        };
    

    while(!feof(_file)){
         if(fgets(fileBuffer, 1024, _file) != NULL) {
        // print the return value (aka string read in) to terminal
            AF_Vertex vertex = {{0,0,0},{0,0,0},{0,0}};
            if(fileBuffer[0] == 'v' && fileBuffer[1] == ' '){
                // vertex
                AF_Vec3 vertPos = AF_Mesh_GetVec3FromString(fileBuffer);
                vertex.position = vertPos;
                //AF_Log("v %f %f %f\n", vertex.position.x, vertex.position.y, vertex.position.z);

                returnMesh.vertices[verticesCount] = vertex;
                // TODO: null check the returned mesh.
                
                verticesCount++;
                continue;
            }
            if(fileBuffer[0] == 'f'){
                // face / indices
                // vertex
                
                // get the first element of each space sperated token
                // Add the indicies 
                char *p = strtok(fileBuffer, " ");
                while(p != NULL) {
                    if((strcmp(p,"f"))){
                        // Add the indicies, the first element in the token is the indicies 
                        returnMesh.indices[indicesCount] = atoi(&p[0]);
                        indicesCount++;
                    }
                    //printf("%s %i %i\n", p, indicesCount, atoi(&p[0]));
                    p = strtok(NULL, " ");
                }
                
                continue;
            }
            if(fileBuffer[0] == 'v' && fileBuffer[1] == 't'){
                // texture coordinate
		AF_Vec2 texPos = AF_Mesh_GetVec2FromString(fileBuffer);
		//vertex.texCoord = texPos;
		// don't overwrite the verts when add the tex coords
		// TODO: fix this
		AF_Vertex tempVertex = returnMesh.vertices[texCoordsCount];
		
		AF_Vertex newVertex = {{tempVertex.position.x,tempVertex.position.y,tempVertex.position.z},{tempVertex.normal.x,tempVertex.normal.y,tempVertex.normal.z},texPos};
                returnMesh.vertices[texCoordsCount] = newVertex;
		texCoordsCount ++;

		continue;
            }
            if(fileBuffer[0] == 'v' && fileBuffer[1] == 'n'){
                // normal
                continue;
            }
        }
    }

    return returnMesh;
}


static inline AF_Mesh AF_Mesh_Load_OBJ(const char* _filePath){
  
    AF_Mesh returnMesh = AF_Mesh_ZERO();
    // open the file
    FILE *file = fopen(_filePath, "r"); // Open the file for reading
    
    if(file == NULL){
        AF_Log_Error("%s Failed to open file %s\n", AF_MESH_FILE_TITLE, _filePath);
        return returnMesh;
    }

    // just get the size of the mesh stored into a AF_Mesh struct
    AF_Mesh tempMesh = AF_Mesh_GetOBJAttribSize(file);

    // Actually load the data into the mesh
    returnMesh = AF_Mesh_Load_Data(file, tempMesh);

   /* 
    AF_Log("Loading Model: \n");
    for(int i = 0; i < returnMesh.vertexCount; i++){
        AF_Vertex vertex = returnMesh.vertices[i];
        AF_Log("%f %f %f %f %f %f %f %f\n",vertex.position.x, vertex.position.y, vertex.position.z, vertex.normal.x, vertex.normal.y, vertex.normal.z, vertex.texCoord.x, vertex.texCoord.y);
    
    }

    AF_Log("Indexes: ");
    for(int i = 0; i < returnMesh.indexCount; i++){
        unsigned int index = returnMesh.indices[i];
        AF_Log("%i, ",index);
    }
    AF_Log("\n");
    */
    /*
    for(int i = 0; i < _mesh->vertexCount; i++){
        //AF_Log("V %f %f %f\n", mesh.vertices[i].position.x, mesh.vertices[i].position.y, mesh.vertices[i].position.z);
    }

    for(int i = 0; i < _mesh->indexCount; i++){
        //AF_Log("I %i\n", mesh.indices[i]);
    }*/

    //AF_Log("Mesh Verticies %d\n", mesh.vertexCount);
    //AF_Log("Mesh Indices %d\n", mesh.indexCount);
    
    // Return a copy of the AF_Mesh struct. It will contain pointers to the heap allocated memory
    returnMesh.has = true;
    returnMesh.enabled = true;
    return returnMesh;
}

inline void AF_Mesh_Destroy(AF_Mesh* _mesh){
    if(_mesh == NULL){
        return;
    }

    free(_mesh->vertices);
    free(_mesh->indices);
    
}



#ifdef __cplusplus
}
#endif  

#endif  // AF_MESH_H
