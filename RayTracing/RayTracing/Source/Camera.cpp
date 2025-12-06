#include "Camera.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	this->eye = eye;

	this->forward = glm::normalize(target - eye);
	this->right = glm::normalize(glm::cross(forward, up));
	this->up = glm::normalize(glm::cross(right, forward));
	
	CalculateViewPlane();
}

ray_t Camera::GetRay(const glm::vec2& uv) const {
	ray_t ray;

	ray.origin = eye;

	glm::vec3 point = lowerLeft + uv.x * horizontal + uv.y * vertical;
	ray.direction = glm::normalize(point - eye);
	
	return ray;
}

void Camera::CalculateViewPlane() {
	float theta = glm::radians(fov);

	float halfHeight = tan(theta * 0.5f);
	float halfWidth = aspectRatio * halfHeight;

	horizontal = right * (halfWidth * 2.0f);
	vertical = up * (halfHeight * 2.0f);

	lowerLeft = eye + forward - (horizontal * 0.5f) - (vertical * 0.5f);
}

