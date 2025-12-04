#include "Renderer.h"
#include "Framebuffer.h"
#include "Camera.h"
<<<<<<< HEAD
#include "Scene.h"
=======
>>>>>>> 7238d2794153f8594556bd414f10e30e243dadf1

#include <iostream>

int main() {
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

<<<<<<< HEAD
	float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	Camera camera(70.0f, aspectRatio);
	camera.SetView({ 0, 0, 5 }, { 0, 0, 0 });

	Scene scene;

=======
	Camera camera(70.0f, aspectRatio);
	camera.SetView({ 0, 0, 5 }, { 0, 0, 0 });

>>>>>>> 7238d2794153f8594556bd414f10e30e243dadf1
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
<<<<<<< HEAD
			
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			
=======

			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}

>>>>>>> 7238d2794153f8594556bd414f10e30e243dadf1
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}

		framebuffer.Clear({ 0, 0, 0, 255 });
		for (int i = 0; i < 300; i++) framebuffer.DrawPoint(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, { 255, 255, 255, 255 });

<<<<<<< HEAD
		scene.Render(framebuffer, camera);
=======
>>>>>>> 7238d2794153f8594556bd414f10e30e243dadf1
		framebuffer.Update();

		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}