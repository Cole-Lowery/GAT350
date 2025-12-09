#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Random.h"
#include "Material.h"
#include <iostream>

int main() {
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;
	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);
	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	float aspectRatio = (float)framebuffer.width / framebuffer.height;//framebuffer width divided by framebuffer height (float division)
	Camera camera(70.0f, aspectRatio);
	camera.SetView({ 0, 2, 5 }, { 0, 0, 0 });
	Scene scene;
/*
	//<unique pointer of Object or auto> sphere = <make unique pointer of Sphere>(glm::vec3{ 0, 0, 0 }, 2.0f, color3_t{ 1, 0, 0 });
	//scene.AddObject(<add the sphere into the scene, remember to move ownership>);
	auto sphere1 = std::make_unique<Sphere>(glm::vec3{ 0, 0, 0 }, 1.0f, color3_t{ 1, 0, 0 });
	scene.AddObject(std::move(sphere1));

	for (int i = 0; i < 5; i++) {
		glm::vec3 position = random::getReal(glm::vec3{ -3.0f }, glm::vec3{ 3.0f });
		auto sphere = std::make_unique<Sphere>(position, 1.0f, color3_t{ 1, 0, 0 });
		scene.AddObject(std::move(sphere)); //<add the sphere into the scene, remember to move ownership>

	}
	*/
	auto red = std::make_shared<Lambertian>(color3_t{ 1.0f, 0.0f, 0.0f });
	auto green = std::make_shared<Lambertian>(color3_t{ 0.0f, 1.0f, 0.0f });
	auto blue = std::make_shared<Lambertian>(color3_t{ 0.0f, 0.0f, 1.0f });
	auto light = std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 3.0f);
	auto metal = std::make_shared<Metal>(color3_t{ 1.0f, 1.0f, 1.0f }, 0.0f);
	std::shared_ptr<Material> materials[] = { red, green, blue, light, metal };

	for (int i = 0; i < 15; i++) {
		glm::vec3 position = random::getReal(glm::vec3{ -3.0f }, glm::vec3{ 3.0f });

		std::unique_ptr<Object> sphere = std::make_unique<Sphere>(Transform{ position }, random::getReal(0.2f, 1.0f), materials[random::getInt(0, 4)]);
		scene.AddObject(std::move(sphere));
	}
	SDL_Event event;
	bool quit = false;

	while (!quit) {
		// check for exit events
		while (SDL_PollEvent(&event)) {
			// window (X) quit
			if (event.type == SDL_EVENT_QUIT) {

				quit = true;

			}
			// escape key quit
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {

				quit = true;

			}

		}
		framebuffer.Clear({ 0, 0, 0, 255 });
		scene.Render(framebuffer, camera, 50);
		framebuffer.Update();
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();

	}

}
