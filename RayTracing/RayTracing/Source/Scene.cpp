#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Object.h"
#include "Color.h"
#include "Random.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples) {
    for (int y = 0; y < framebuffer.height; y++) {
        for (int x = 0; x < framebuffer.width; x++) {

            color3_t color = color3_t{ 0.0f };

            for (int i = 0; i < numSamples; i++) {

                glm::vec2 pixel{ x, y };

                pixel += glm::vec2{
                    random::getReal<float>(),
                    random::getReal<float>()
                };

                glm::vec2 point = pixel / glm::vec2{ framebuffer.width, framebuffer.height };

                point.y = 1.0f - point.y;

                ray_t ray = camera.GetRay(point);

                color += Trace(ray, 0.0f, 100.0f);
            }

            color /= (float)numSamples;

            framebuffer.DrawPoint(x, y, ColorConvert(color));
        }
    }
}


void Scene::AddObject(std::unique_ptr<Object> object) {
	objects.push_back(std::move(object));
}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance) {

	raycastHit_t raycastHit;

	bool rayHit = false;
	float closestDistance = maxDistance;

	for (auto& object : objects) {

		if (object->Hit(ray, minDistance, closestDistance, raycastHit)) {
			rayHit = true;
			closestDistance = raycastHit.distance;
		}
	}

	if (rayHit) {
		return raycastHit.color;
	}

	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1.0f) * 0.5f;

	color3_t color = glm::mix(skyBottom, skyTop, t);
	return color;
}
