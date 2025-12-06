#pragma once
#include "Ray.h"

class Object
{
    public:
        Object() = default;
        Object(const color3_t& color) : color(color) {}

        virtual bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0;

    protected:
        color3_t color;
};