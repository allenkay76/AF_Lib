#pragma once
class CCollision2D{
    public:
        CCollision2D(const float _r) 
        : 
        has(false),
        enabled(false),
        radius(_r){}

        CCollision2D() 
        : 
        has(false),
        enabled(false),
        radius(0){}
        
        ~CCollision2D(){}

        bool has = false;
        bool enabled = false;
        float radius = 0;
};