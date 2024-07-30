#pragma once

// Simple 2d collider component

struct CollisionRect {
    float x, y, w, h;
};

struct Collider2D {
    bool has = false;
    bool enabled = false;
    float gravity = 1;
    CollisionRect collisionRect;
};