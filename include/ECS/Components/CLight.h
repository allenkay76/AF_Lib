#pragma once
#include "glm/vec3.hpp"
#include "ECS/Components/CTransform3D.h"

enum LightType{
    Directional,
    PointLight,
    SpotLight
};

class CLight{
    public:

    // Constructor with params
        CLight(LightType _lightType, const glm::vec3 _ambient, const glm::vec3 _diffuse, const float _constant, const float _linear, const float _quadratic) :
        has(false),
        enabled(false),
        lightType(_lightType),
        ambient(_ambient),
        diffuse(_diffuse),
        constant(_constant),
        linear(_linear),
        quadratic(_quadratic){}

        // Constructor without params
        
        CLight() :
        has(false),
        enabled(false),
        lightType(LightType::PointLight),
        ambient(glm::vec3(0,0,0)),
        diffuse(glm::vec3(0,0,0)),
        constant(0),
        linear(0),
        quadratic(0) {}
        
        bool has = false;
        bool enabled = false;
        LightType lightType;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        float constant = 0;
        float linear = 0;
        float quadratic = 0;
        
};