#include "Material.h"
#include "Random.h"
#include <iostream>

bool Lambertian::Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const {
    glm::vec3 scatterDirection = raycastHit.normal + random::inUnitSphere();
    if (glm::length(scatterDirection) < 1e-6f) scatterDirection = raycastHit.normal;
    scattered.origin = raycastHit.point;
    scattered.direction = glm::normalize(scatterDirection);
    attenuation = albedo;
    return true;
}

bool Metal::Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const {
    glm::vec3 reflected = glm::reflect(glm::normalize(incident.direction), raycastHit.normal);
    scattered.origin = raycastHit.point;
    scattered.direction = glm::normalize(reflected + random::inUnitSphere() * fuzz);
    attenuation = albedo;
    return (glm::dot(scattered.direction, raycastHit.normal) > 0);

}

static float Schlick(float cosine, float refractiveIndex) {
    float r0 = (1.0f - refractiveIndex) / (1.0f + refractiveIndex);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * std::pow((1.0f - cosine), 5.0f);
}

bool Dielectric::Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const {
    glm::vec3 outNormal;
    float ni_over_nt;
    float cosine;
    glm::vec3 unitDir = glm::normalize(incident.direction);
    if (glm::dot(unitDir, raycastHit.normal) < 0) {
        outNormal = raycastHit.normal;
        ni_over_nt = 1.0f / refractiveIndex;
        cosine = -glm::dot(unitDir, raycastHit.normal);
    }
    else {
        outNormal = -raycastHit.normal;
        ni_over_nt = refractiveIndex;
        cosine = refractiveIndex * glm::dot(unitDir, raycastHit.normal);
    }
    glm::vec3 refracted = glm::refract(unitDir, outNormal, ni_over_nt);
    float reflectProbability = (glm::length(refracted) > 0.0f) ? Schlick(cosine, refractiveIndex) : 1.0f;
    glm::vec3 reflected = glm::reflect(unitDir, raycastHit.normal);
    if (random::getReal() < reflectProbability) {
        scattered = { raycastHit.point, reflected };
    }
    else {
        scattered = { raycastHit.point, refracted };
    }
    attenuation = albedo;
    return true;
}
