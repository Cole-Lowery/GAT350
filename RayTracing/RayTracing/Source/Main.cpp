#include "Renderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Random.h"

#include <iostream>

int main() {
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	Camera camera(70.0f, aspectRatio);
	camera.SetView({ 0, 0, 5 }, { 0, 0, 0 });

	Scene scene;

	scene.AddObject(std::make_unique<Sphere>(
		glm::vec3{ 0, 0, 0 },
		1.5f,
		color3_t{ 1, 0, 0 }
	));

	for (int i = 0; i < 5; i++) {
		glm::vec3 pos{
			random::getReal(-3.0f, 3.0f),
			random::getReal(-3.0f, 3.0f),
			random::getReal(-3.0f, 3.0f)
		};

		color3_t col{
			random::getReal(0.0f, 1.0f),
			random::getReal(0.0f, 1.0f),
			random::getReal(0.0f, 1.0f)
		};

		scene.AddObject(std::make_unique<Sphere>(pos, 1.0f, col));
	}

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}

		framebuffer.Clear({ 0, 0, 0, 255 });
		for (int i = 0; i < 300; i++) framebuffer.DrawPoint(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, { 255, 255, 255, 255 });

		scene.Render(framebuffer, camera, 50);
		framebuffer.Update();

		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}