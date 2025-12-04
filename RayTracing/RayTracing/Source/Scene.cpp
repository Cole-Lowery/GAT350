#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera) {
	for (int y = 0; y < framebuffer.height; y++) {
		for (int x = 0; x < framebuffer.width; x++)	{

			glm::vec2 pixel = glm::vec2{ x,y }; 
			glm::vec2 point = pixel / glm::vec2{ framebuffer.width, framebuffer.height }; 

			point.y = 1.0f - point.y;

			ray_t ray = camera.GetRay(point);
			color3_t color = Trace(ray);

			framebuffer.DrawPoint(x, y, ColorConvert(color));
		}
	}
}

color3_t Scene::Trace(const ray_t& ray) {
	glm::vec3 direction = glm::normalize(ray.direction);

	float t = (direction.y + 1.0f) * 0.5f;
	
	color3_t color = glm::mix(skyBottom, skyTop, t);

	return color;
}
