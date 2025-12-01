#include "PostProcessComponent.h"
#include "Engine.h"

namespace neu {
	FACTORY_REGISTER(PostProcessComponent)

		void PostProcessComponent::Update(float dt) {
	}

	void PostProcessComponent::Apply(Program& program) {
		program.SetUniform("u_parameters", (uint32_t)parameters);
		program.SetUniform("u_colorTint", colorTint);
		// set time (animated noise)	
		program.SetUniform("u_time", GetEngine().GetTime().GetTime());
		//program.SetUniform(<set u_blend>);
		program.SetUniform("u_blend", blend);
	}

	void PostProcessComponent::Read(const serial_data_t& value) {
		Object::Read(value);
	}

	void PostProcessComponent::UpdateGui() {
		uint32_t iparameters = (uint32_t)parameters;

		bool parameter = iparameters & (uint32_t)Parameters::GrayScale;
		if (ImGui::Checkbox("Gray Scale", &parameter)) {
			if (parameter) iparameters |= (uint32_t)Parameters::GrayScale;
			else iparameters &= ~(uint32_t)Parameters::GrayScale;
		}

		parameter = iparameters & (uint32_t)Parameters::ColorTint;
		if (ImGui::Checkbox("Color Tint", &parameter)) {
			if (parameter) iparameters |= (uint32_t)Parameters::ColorTint;
			else iparameters &= ~(uint32_t)Parameters::ColorTint;
		}


			parameters = (Parameters)iparameters;

		ImGui::ColorEdit3("Color Tint", glm::value_ptr(colorTint));
		ImGui::SliderFloat("Blend", &blend, 0.0f, 1.0f);
		//ImGui::SliderFloat(<set blend, range is 0 - 1>);
	}
}