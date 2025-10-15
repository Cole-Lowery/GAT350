#include "Mesh.h"
#include "Renderer.h"

namespace neu {
	bool Mesh::Load(const std::string& filename) {

		std::string buffer;
		if (!file::ReadTextFile(filename, buffer)) {
			LOG_ERROR("Could not read file: {}", filename);
			return false;
		}

		std::stringstream stream(buffer);

		// read color
		stream >> m_color;

		// read points
		vec2 point;
		while (stream >> point) {
			m_points.push_back(point);
		}

		if (!stream.eof()) {
			LOG_ERROR("Could not parse file: {}", filename);
			return false;
		}

		return true;
	}

	/// <summary>
	/// Draws the model by rendering lines between its points using the specified renderer.
	/// </summary>
	/// <param name="renderer">The Renderer object used to draw the model.</param>
	

	/// <summary>
	/// Draws the model using the specified renderer and transformation.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the model.</param>
	/// <param name="transform">The transformation to apply, including position, rotation, and scale.</param>


	/// <summary>
	/// Calculates and updates the model's radius as the maximum distance from the origin among all points.
	/// </summary>

}