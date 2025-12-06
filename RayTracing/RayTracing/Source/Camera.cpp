#include "Camera.h"

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	this->eye = eye;

	// create camera axis
	this->forward = normalize(target - eye); //normalized direction vector (target <-- eye)
	this->right = normalize(cross(forward, up)); //normalized vector from the cross product of the forward and up vector
	this->up = normalize(cross(right, forward)); //normalized vector from the cross product of the right and forward vector

	CalculateViewPlane();
}

ray_t Camera::GetRay(const glm::vec2& uv) const {
	ray_t ray;

	ray.origin = eye;
	ray.direction = lowerLeft + horizontal * uv.x + vertical * uv.y - eye; //lower left position + horizontal vector * uv.x + vertical vector * uv.y - camera eye;

	return ray;
}

void Camera::CalculateViewPlane() {
	float theta = glm::radians(fov);

	float halfHeight = glm::tan(theta * 0.5f);//trig function that is opposite over adjacent, use half theta as parameter
	float halfWidth = halfHeight * aspectRatio;//scale halfHeight by aspect ratio

	horizontal = right * (halfWidth * 2);//right vector * width (how do you get full width from half width?)
	vertical = up * (halfHeight * 2);//up vector * height (how do you get full height from half height?)

	lowerLeft = eye - (right * halfWidth) - (up * halfHeight) + forward;
	//lowerLeft = eye - (half horizontal) - (half vertical) + forward;
}

