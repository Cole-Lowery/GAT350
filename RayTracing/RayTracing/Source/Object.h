#pragma once

#include <memory>

#include "Ray.h"

#include "Transform.h"

#include "Color.h"

class Object

{

public:

	Object() = default;

	//Object(const color3_t& color) { this->color = color; } //? ? ? 

	Object(const Transform& transform, std::shared_ptr<class Material> material) :

		transform{ transform },

		material{ material }

	{
	}

	virtual bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0;

protected:

	Transform transform;

	std::shared_ptr<class Material> material;

};

