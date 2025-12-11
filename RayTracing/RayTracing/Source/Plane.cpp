#include "Plane.h"
#include "Ray.h"
#include <glm/gtx/norm.hpp>

bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
    float t;

    glm::vec3 center = transform.position;
    glm::vec3 normal = transform.up();

    if (!Raycast(ray, center, normal, minDistance, maxDistance, t))
        return false;

    raycastHit.distance = t;
    raycastHit.point = ray.origin + ray.direction * t;
    raycastHit.normal = glm::normalize(normal);
    raycastHit.material = material.get();

    return true;
}

bool Plane::Raycast(const ray_t& ray,
    const glm::vec3& point,
    const glm::vec3& normal,
    float minDistance,
    float maxDistance,
    float& t)
{
    float denominator = glm::dot(ray.direction, normal);

    if (std::abs(denominator) < glm::epsilon<float>()) {
        return false;
    }

    t = glm::dot(point - ray.origin, normal) / denominator;

    if (t <= minDistance || t >= maxDistance) {
        return false;
    }

    return true;
}
