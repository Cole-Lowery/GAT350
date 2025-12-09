#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"
#include "Object.h"
#include "Random.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples)
{
    for (int y = 0; y < framebuffer.height; y++)
    {
        for (int x = 0; x < framebuffer.width; x++)
        {
            color3_t pixelColor{ 0.0f };

            for (int i = 0; i < numSamples; i++)
            {
                glm::vec2 pixel = glm::vec2(x, y);
                pixel += glm::vec2(random::getReal<float>(), random::getReal<float>());

                glm::vec2 uv = pixel / glm::vec2(framebuffer.width, framebuffer.height);
                uv.y = 1.0f - uv.y;

                ray_t ray = camera.GetRay(uv);

                pixelColor += Trace(ray, 0.001f, 10000.0f, 5);
            }

            pixelColor /= (float)numSamples;

            pixelColor = glm::sqrt(pixelColor);

            framebuffer.DrawPoint(x, y, ColorConvert(pixelColor));
        }
    }
}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, int maxDepth)
{
    if (maxDepth <= 0) {
        return color3_t{ 0.0f };
    }

    raycastHit_t hit;
    bool rayHit = false;
    float closestDistance = maxDistance;

    for (auto& object : objects) {
        raycastHit_t tempHit;
        if (object->Hit(ray, minDistance, closestDistance, tempHit)) {
            rayHit = true;
            closestDistance = tempHit.distance;
            hit = tempHit;
        }
    }

    if (rayHit) {
        color3_t attenuation;
        ray_t scattered;

        if (hit.material->Scatter(ray, hit, attenuation, scattered)) {
            return attenuation * Trace(scattered, minDistance, maxDistance, maxDepth - 1);
        }
        else {
            return hit.material->GetEmissive();
        }
    }

    float t = 0.5f * (ray.direction.y + 1.0f);
    return (1.0f - t) * skyBottom + t * skyTop;
}