#pragma once
class CCollision3D{
    public:
        CCollision3D(const float _r) 
        : 
        has(false),
        enabled(false),
        radius(_r){}

        CCollision3D() 
        : 
        has(false),
        enabled(false),
        radius(0){}
        
        ~CCollision3D(){}

        bool has = false;
        bool enabled = false;
        float radius = 0;
};