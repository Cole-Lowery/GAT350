#pragma once
#include <memory>
#include "Color.h"
#include "Ray.h"
#include "Transform.h"

class Material
{
public:
	Material() = default;
	Material(const color3_t& albedo) : albedo{ albedo } {}
	virtual ~Material() = default;

	virtual bool Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const = 0;

	const color3_t& GetColor() const { return albedo; }
	virtual color3_t GetEmissive() const { return color3_t{ 0, 0, 0 }; }

protected:
	color3_t albedo{ 0, 0, 0 };
};

class Lambertian : public Material
{
public:
	Lambertian(const color3_t& albedo) : Material{ albedo } {}

	bool Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const override;
};

class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : Material{ albedo }, fuzz{ std::clamp(fuzz, 0.0f, 1.0f) } {}

	bool Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const override;

private:
	float fuzz = 0;
};

class Dielectric : public Material
{
public:
	Dielectric(const glm::vec3& albedo, float refractiveIndex) : Material{ albedo }, refractiveIndex{ std::max(refractiveIndex, 1.0f) } {}

	bool Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const override;

private:
	float refractiveIndex = 0;
};

class Emissive : public Material
{
public:
	Emissive(const color3_t& albedo, float intensity = 1) : Material{ albedo }, intensity{ intensity } {}

	bool Scatter(const ray_t& incident, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const override { return false; }

	color3_t GetEmissive() const override { return albedo * intensity; }

private:
	float intensity{ 1 };
};