#include "Material.h"
#include "Random.h"
#include <iostream>

bool Lambertian::Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const {
    scattered.origin = raycastHit.point;
    scattered.direction = glm::normalize(raycastHit.normal + random::onUnitSphere());

    attenuation = albedo;

    return true;
}

bool Metal::Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const {
    glm::vec3 reflected = glm::reflect(glm::normalize(incident.direction), raycastHit.normal);

    scattered.origin = raycastHit.point;
    scattered.direction = glm::normalize(reflected + random::onUnitSphere() * fuzz);

    attenuation = albedo;

    return glm::dot(scattered.direction, raycastHit.normal);
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

    glm::vec3 rayDirection = glm::normalize(incident.direction);

    if (glm::dot(incident.direction, raycastHit.normal) < 0) {
        outNormal = raycastHit.normal;
        ni_over_nt = 1.0f / refractiveIndex;
        cosine = -glm::dot(rayDirection, raycastHit.normal);
    }
    else {
        outNormal = -raycastHit.normal;
        ni_over_nt = refractiveIndex;
        cosine = refractiveIndex * glm::dot(rayDirection, raycastHit.normal);
    }

    glm::vec3 refracted = glm::refract(rayDirection, outNormal, ni_over_nt);
    float reflectProbability = 1.0f;

    if (glm::length(refracted) > 0.0f) {
        reflectProbability = Schlick(cosine, refractiveIndex);
    }

    glm::vec3 reflected = glm::reflect(rayDirection, raycastHit.normal);

    scattered = (random::getReal() < reflectProbability) ? ray_t{ raycastHit.point, reflected } : ray_t{ raycastHit.point, refracted };
    attenuation = albedo;

    return true;
}