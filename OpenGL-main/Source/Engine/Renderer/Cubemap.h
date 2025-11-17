#pragma once
#include "Texture.h"

namespace neu {
	class Cubemap : public Texture {
	public:
		//CLASS_PROTOTYPE(Cubemap)

		bool Load(const std::string& filenames);

		void UpdateGui() override {}
	};

}