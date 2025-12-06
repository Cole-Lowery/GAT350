#pragma once
#include <glm/glm.hpp>
#include "Color.h"


struct ray_t {
public:
	glm::vec3 origin;
	glm::vec3 direction;
	
	ray_t() = default;
	ray_t(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(direction) {}

	glm::vec3 at(float t) const {
		return origin + t * direction;
	}

	glm::vec3 operator * (float t) const { return origin + direction * t; }
};

struct raycastHit_t {
	glm::vec3 point;
	glm::vec3 normal;
	float distance;
	color3_t color;
};
