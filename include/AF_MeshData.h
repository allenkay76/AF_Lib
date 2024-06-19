#ifndef AF_MESH_DATA_H
#define AF_MESH_DATA_H
#include "AF_Mesh.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    // array of meshes
    AF_Mesh* meshes;
    int numMeshes;
} AF_MeshData;

inline int AF_MeshData_Destroy(AF_MeshData* _meshData){
    if(_meshData == NULL){
        return 0;
    }
    free(_meshData->meshes);
    return 1;
}

#ifdef __cplusplus
}
#endif

#endif //AF_MESH_DATA_H
