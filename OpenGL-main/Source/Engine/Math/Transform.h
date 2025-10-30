#pragma once
#include "Renderer/GUI.h"
#include "Core/Serializable.h"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

namespace neu {
    /// <summary>
    /// Represents a 2D transformation containing position, rotation, and uniform scale.
    /// 
    /// The Transform struct is a fundamental component in 2D graphics and game engines,
    /// encapsulating the three basic transformations that define an object's spatial
    /// properties in 2D space. It implements ISerializable to support loading transform
    /// data from configuration files and save systems.
    /// 
    /// Mathematical Foundation:
    /// - Position: Translation in 2D space (x, y coordinates)
    /// - Rotation: Angular orientation in radians around the object's center
    /// - Scale: Uniform scaling factor applied to both x and y dimensions
    /// 
    /// Transformation Order:
    /// The typical transformation order is Scale → Rotate → Translate (SRT),
    /// which means scaling happens first, then rotation, then translation.
    /// This order ensures intuitive behavior where objects scale around their
    /// center, rotate around their center, then move to their final position.
    /// 
    /// Common Use Cases:
    /// - Game object positioning and orientation (players, enemies, items)
    /// - UI element layout and positioning
    /// - Sprite rendering transformations
    /// - Physics body transformations
    /// - Camera transformations for view matrices
    /// - Particle system transformations
    /// - Animation keyframe data
    /// 
    /// Integration with Graphics Systems:
    /// - Can be converted to transformation matrices for rendering
    /// - Compatible with 2D graphics APIs (OpenGL, DirectX, etc.)
    /// - Supports hierarchical transformations (parent-child relationships)
    /// - Enables efficient batch transformations for multiple objects
    /// 
    /// Performance Considerations:
    /// - Lightweight structure with minimal memory overhead
    /// - Efficient for frequent updates (movement, rotation, scaling)
    /// - Matrix conversion can be cached when transformation doesn't change
    /// - Suitable for real-time applications and game loops
    /// </summary>
    struct Transform : public ISerializable, GUI {
        glm::vec3 position{ 0, 0, 0 };
        glm::vec3 rotation{ 0, 0, 0 };
        glm::vec3 scale{ 1, 1, 1 };

        Transform() = default;
        Transform(const glm::vec3& position, const glm::vec3& rotation = { 0, 0, 0 }, const glm::vec3& scale = { 1, 1, 1 }) :
            position{ position },
            rotation{ rotation },
            scale{ scale }
        {
        }

        glm::mat4 GetMatrix() const {
            glm::mat4 mx = glm::mat4(1.0f);
            mx = glm::translate(mx, position);
            mx *= glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
            mx = glm::scale(mx, scale);

			return mx;
        }

        operator glm::mat4 () const {
            return GetMatrix();
		}
        
        void Read(const serial_data_t& value) override;

        void UpdateGui() override;
    };
}