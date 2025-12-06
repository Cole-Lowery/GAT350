#pragma once
#include "Color.h"
#include <glm/glm.hpp>

struct ray_t
{
    glm::vec3 origin;
    glm::vec3 direction;

    ray_t() = default;
    ray_t(glm::vec3& origin, glm::vec3& direction) : origin(origin), direction(direction) {}

    glm::vec3 at(float t) const { return origin + direction * t; }
    glm::vec3 operator * (float t) const { return origin + direction * t; }
};

struct raycastHit_t
{
    glm::vec3 point;
    glm::vec3 normal;
    float distance;

    color3_t color;
};