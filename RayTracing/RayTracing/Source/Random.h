#pragma once
#include <cstdlib>
#include <random>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>



namespace random {

    inline std::mt19937& generator() {
        // Hardware-based random device for seeding (when available)
        static std::random_device rd;
        // Mersenne Twister generator, seeded once on first access
        static std::mt19937 gen(rd());
        return gen;
    }

    inline void seed(unsigned int value) {
        generator().seed(value);
    }


    inline int getInt(int min, int max) {
        // Uniform distribution ensures each value in range has equal probability
        std::uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }


    inline int getInt(int max) {
        return getInt(0, max - 1);
    }


    inline int getInt() {
        // Static distribution to avoid recreation overhead
        static std::uniform_int_distribution<> dist;
        return dist(generator());
    }

    template <typename T = float>
    inline T getReal(T min, T max) {
        // Uniform real distribution for floating-point values
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }


    template <typename T = float>
    inline T getReal(T max) {
        return getReal(static_cast<T>(0), static_cast<T>(max));
    }


    template <typename T = float>
    inline T getReal() {
        // Static distribution to avoid recreation overhead
        static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

    inline glm::vec3 getReal(const glm::vec3& min, const glm::vec3& max) {
        return glm::vec3{
            getReal(min.x, max.x),
            getReal(min.y, max.y),
            getReal(min.z, max.z),
        };
    }

    inline bool getBool() {
        // Bernoulli distribution with p=0.5 for fair coin flip
        static std::bernoulli_distribution dist(0.5);
        return dist(generator());
    }

    inline glm::vec2 onUnitCircle() {
        // Generate random angle in range [0, 2π)
        float radians = getReal(glm::two_pi<float>());

        // Convert polar coordinates to Cartesian coordinates
        // cos(θ) gives x-component, sin(θ) gives y-component
        return glm::vec2{ std::cos(radians), std::sin(radians) };
    }

    inline glm::vec3 inUnitSphere() {
        glm::vec3 v;

        do {
            v = getReal(glm::vec3{ -1 }, glm::vec3{ 1 });

        } while(glm::length2(v) > 1.0f);

        return v;
    }

    inline glm::vec3 onUnitSphere() {
        return glm::normalize(inUnitSphere());
    }
}