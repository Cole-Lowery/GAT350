#pragma once
#include <SDL3/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <algorithm>
#include <glm/gtc/color_space.hpp>

using color3_t = glm::vec3;
using color4_t = glm::vec4;

inline float LinearToGamma(float linear) {
	return (linear > 0) ? std::sqrt(linear) : 0;
}
/*
inline color3_t HSVtoRGB(const color3_t& hsv) {
	return glm::rgbColor(hsv);
}

inline color3_t HSVtoRGB(float hue, float saturation, float value) {
	return glm::rgbColor(glm::vec3{ hue, saturation, value });
}
*/

inline SDL_Color ColorConvert(const color4_t& color4)
{
	SDL_Color color;

	color.r = static_cast<Uint8>(glm::clamp(LinearToGamma(color4.r), 0.0f, 1.0f) * 255.0f);
	color.g = static_cast<Uint8>(glm::clamp(LinearToGamma(color4.g), 0.0f, 1.0f) * 255.0f);
	color.b = static_cast<Uint8>(glm::clamp(LinearToGamma(color4.b), 0.0f, 1.0f) * 255.0f);
	color.a = static_cast<Uint8>(glm::clamp(color4.a, 0.0f, 1.0f) * 255.0f);

	return color;
}

inline SDL_Color ColorConvert(const color3_t& color3)
{
	SDL_Color color;

	color.r = static_cast<Uint8>(glm::clamp(LinearToGamma(color3.r), 0.0f, 1.0f) * 255.0f);
	color.g = static_cast<Uint8>(glm::clamp(LinearToGamma(color3.g), 0.0f, 1.0f) * 255.0f);
	color.b = static_cast<Uint8>(glm::clamp(LinearToGamma(color3.b), 0.0f, 1.0f) * 255.0f);
	color.a = 255;

	return color;
}

inline color4_t ColorConvert(const SDL_Color& color)
{
	color4_t color4;

	color4.r = color.r / 255.0f;
	color4.g = color.g / 255.0f;
	color4.b = color.b / 255.0f;
	color4.a = color.a / 255.0f;

	return color4;
}