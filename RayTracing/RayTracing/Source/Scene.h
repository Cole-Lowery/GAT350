#pragma once
#include "Color.h"
#include <vector>
#include <memory>

class Scene
{
public:
	Scene() = default;

	void Render(class Framebuffer& framebuffer, const class Camera& camera);
	void SetSky(const color3_t& skyBottom, const color3_t& skyTop) {
		this->skyBottom = skyBottom;
		this->skyTop = skyTop;
	}

private:
	color3_t Trace(const struct ray_t& ray);

private:
	color3_t skyBottom{ 1 };
	color3_t skyTop{ 0.5f, 0.7f, 1.0f };
};