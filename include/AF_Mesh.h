#ifndef AF_MESH_H
#define AF_MESH_H
#include "AF_Vertex.h"
#include <stdio.h>
#include <string.h>

#include "AF_Log.h"

#ifdef __cplusplus
extern "C" {
#endif  
const char* fileTitle = "AF_Mesh: ";
typedef struct {
    AF_Vertex* vertices;
    int vertexCount;
    int* indices;
    int indexCount;
} AF_Mesh;

inline AF_Vec2 AF_Mesh_GetVec2FromString(char* _buffer){ //, uint16_t _size){
    AF_Vec2 returnVec2;
    char* token = strtok(_buffer, " ");
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

inline AF_Vec3 AF_Mesh_GetVec3FromString(char* _buffer){ //, uint16_t _size){
    AF_Vec3 returnVec3;
    char* token = strtok(_buffer, " ");
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

inline AF_Mesh AF_Mesh_GetOBJAttribSize(FILE* _file){
    AF_Mesh mesh = {NULL, 0, NULL, 0};
    if(_file == NULL){
        AF_Log_Error("%s Failed to open file to GetOBJAttribSize %s", fileTitle);
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
            AF_Vertex vertex;
            if(fileBuffer[0] == 'v' && fileBuffer[1] == ' '){
                // vertex
                AF_Vec3 vertPos = AF_Mesh_GetVec3FromString(fileBuffer);
                vertex.position = vertPos;
                mesh.vertexCount++;
                continue;
            }
            if(fileBuffer[0] == 'f'){
                // face / indices
                // add 4 faces to the index count
                mesh.indexCount+=4;
                continue;
            }
            if(fileBuffer[0] == 'v' && fileBuffer[1] == 't'){
                // texture coordinate
                //AF_Vec2 texPos = AF_Mesh_GetVec2FromString(fileBuffer);
                //vertex.texCoord = texPos;
                //AF_Log("vt %f %f\n", vertex.texCoord.x, vertex.texCoord.y);
                //mesh.vertexCount++;
                continue;
            }
            if(fileBuffer[0] == 'v' && fileBuffer[1] == 'n'){
                // normal
                //AF_Vec3 normPos = AF_Mesh_GetVec3FromString(fileBuffer);
                //vertex.normal = normPos;
                //AF_Log("vn %f %f %f\n", vertex.normal.x, vertex.normal.y, vertex.normal.z);
                //mesh.vertexCount++;
                continue;
            }
        }
    }
    // Move back to the beginning of the file using fseek and rewind
    fseek(_file, 0L, SEEK_SET);
    rewind(_file);
    return mesh;
}

inline int AF_Mesh_Load_Data(FILE* _file, AF_Mesh* _mesh){
    int verticesCount = 0;
    int indicesCount = 0;
    char fileBuffer[1024] ; // Buffer for reading the file
    while(!feof(_file)){
         if(fgets(fileBuffer, 1024, _file) != NULL) {
        // print the return value (aka string read in) to terminal
            AF_Vertex vertex;
            if(fileBuffer[0] == 'v' && fileBuffer[1] == ' '){
                // vertex
                AF_Vec3 vertPos = AF_Mesh_GetVec3FromString(fileBuffer);
                vertex.position = vertPos;
                AF_Log("v %f %f %f\n", vertex.position.x, vertex.position.y, vertex.position.z);

                _mesh->vertices[verticesCount] = vertex;
                verticesCount++;
                continue;
            }
            if(fileBuffer[0] == 'f'){
                // face / indices
                // vertex
                // get the first element of each space sperated token
                char* token = strtok(fileBuffer, " ");
                int index = 0;
                if(token != NULL){
                    // face 1
                    token = strtok(NULL, " ");
                    index = strtof(token, NULL);
                    _mesh->indices[indicesCount] = index;
                    indicesCount++;
                    AF_Log("i %i\n", index);

                    // face 2
                    token = strtok(NULL, " ");
                    index = strtof(token, NULL);
                    _mesh->indices[indicesCount] = index;
                    indicesCount++;
                    AF_Log("i %i\n", index);

                    // face 3
                    token = strtok(NULL, " ");
                    index = strtof(token, NULL);
                    _mesh->indices[indicesCount] = index;
                    indicesCount++;
                    AF_Log("i %i\n", index);

                    // face 4
                    token = strtok(NULL, " ");
                    index = strtof(token, NULL);
                    _mesh->indices[indicesCount] = index;
                    indicesCount++;
                    AF_Log("i %i\n", index);
                }
                

                
                continue;
            }
            if(fileBuffer[0] == 'v' && fileBuffer[1] == 't'){
                // texture coordinate
                //AF_Vec2 texPos = AF_Mesh_GetVec2FromString(fileBuffer);
                //vertex.texCoord = texPos;
                //AF_Log("vt %f %f\n", vertex.texCoord.x, vertex.texCoord.y);
                //mesh.vertexCount++;
                continue;
            }
            if(fileBuffer[0] == 'v' && fileBuffer[1] == 'n'){
                // normal
                //AF_Vec3 normPos = AF_Mesh_GetVec3FromString(fileBuffer);
                //vertex.normal = normPos;
                //AF_Log("vn %f %f %f\n", vertex.normal.x, vertex.normal.y, vertex.normal.z);
                //mesh.vertexCount++;
                continue;
            }
        }
    }
    return 0;
}


inline static int AF_Mesh_Load_OBJ(const char* _filePath, AF_Mesh* _mesh){
    if(_mesh == NULL){
        return 0;
    }
    
    // open the file
    FILE *file = fopen(_filePath, "r"); // Open the file for reading
    
    if(file == NULL){
        AF_Log_Error("%s Failed to open file %s", fileTitle, _filePath);
        return 0;
    }

    AF_Mesh mesh;
    mesh = AF_Mesh_GetOBJAttribSize(file);

    // Create verticies array of size vertexCount
    mesh.vertices = (AF_Vertex*)malloc(sizeof(AF_Vertex) * mesh.vertexCount);

    // create indices array of size indexCount
    mesh.indices = (int*)malloc(sizeof(int) * mesh.indexCount);
    AF_Mesh_Load_Data(file, &mesh);
    for(int i = 0; i < mesh.vertexCount; i++){
        AF_Log("V %f %f %f\n", mesh.vertices[i].position.x, mesh.vertices[i].position.y, mesh.vertices[i].position.z);
    }

    for(int i = 0; i < mesh.indexCount; i++){
        AF_Log("I %i\n", mesh.indices[i]);
    }

    AF_Log("Mesh Verticies %d\n", mesh.vertexCount);
    AF_Log("Mesh Indices %d\n", mesh.indexCount);
    
    return 1;
}

void AF_Mesh_Destroy(AF_Mesh* _mesh){
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
