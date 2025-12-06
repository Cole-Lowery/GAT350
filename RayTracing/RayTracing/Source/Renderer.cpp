#include "Camera.h"
#include "Framebuffer.h"
#include "Renderer.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include <iostream>
#include "Random.h"

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Renderer::Initialize()
{
    // initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

bool Renderer::CreateWindow(const std::string& name, int width, int height, bool fullscreen)
{
    this->width = width;
    this->height = height;

    // create window
    // returns pointer to window if successful or nullptr if failed
    window = SDL_CreateWindow(name.c_str(),
        width, height,
        (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
    if (window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    
    // create renderer
    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr)
    {
        std::cerr << "Error creating SDL renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}


void Renderer::Show() {
    // present the renderer to the screen
    SDL_RenderPresent(renderer);
}

void Renderer::CopyFramebuffer(const Framebuffer& framebuffer) {
    // copies the framebuffer texture to the renderer for display
    SDL_RenderTexture(renderer, framebuffer.texture, NULL, NULL);
}

void Renderer::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples){
	Scene scene;
    for (int y = 0; y < framebuffer.height; y++) {
        for (int x = 0; x < framebuffer.width; x++) {
                color3_t color{ 0 };
            for (int s = 0; s < 500; s++) {
                glm::vec2 pixel{ x, y };
				pixel += glm::vec2{ random::getReal(0.0f, 1.0f), random::getReal(0.0f, 1.0f) }; 

                glm::vec2 point = pixel / glm::vec2{ framebuffer.width, framebuffer.height };
                point.y = 1 - point.y;

                ray_t ray = camera.GetRay(point);

                raycastHit_t raycastHit; 
				color += scene.Trace(ray, 0, 100, raycastHit);
            }
            color = color / static_cast<float>(numSamples);
            framebuffer.DrawPoint(x, y, ColorConvert(color));
        }
    }
}