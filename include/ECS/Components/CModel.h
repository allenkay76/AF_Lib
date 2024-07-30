#pragma once
#include "glm/vec3.hpp"
#include "Rendering/AF_Vertex.h"

struct CModel{
    CModel(const char* _modelPath, const char* _modelTexColPath) :
        has(false),
        enabled(false),
        modelIndex(0),
        modelPath(_modelPath),
        modelTexColPath(_modelTexColPath),
        modelTexNormPath(""),
        modelTexSpecPath(""),
        shaderID(0),
        indicesSize(0),
        bufferStartIndex(0),
        vertices({}),
        indices({}),
        shininess(32.0f),
        specularColor(0.1, 0.1, 0.1) {}

        // Constructor without params
        
    CModel() :
        has(false),
        enabled(false),
        modelIndex(0),
        modelPath(""),
        modelTexColPath(""),
        modelTexNormPath(""),
        modelTexSpecPath(""),
        shaderID(0),
        indicesSize(0),
        bufferStartIndex(0),
        vertices({}),
        indices({}),
        shininess(38.0f),
        specularColor(0.1, 0.1, 0.1) {}

    bool has = false;
    bool enabled = false;
    uint32_t modelIndex;
    const char* modelPath;
    const char* modelTexColPath;
    const char* modelTexNormPath;
    const char* modelTexSpecPath;
    uint32_t shaderID;
    const char* fragShaderPath;
    const char* vertShaderPath;
    size_t indicesSize;
    unsigned int bufferStartIndex;
    std::vector<AF_Vertex> vertices;
    std::vector<uint32_t> indices;
    float shininess;
    glm::vec3 specularColor;
    //CTransform3D& transformPtr;
};