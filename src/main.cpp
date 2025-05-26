#include <iostream>

#include "Ecs.h"
#include "Renderer.h"
#include "Window.h"

std::vector<Vertex> vertices = {
    {{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // 0
    {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}}, // 1
    {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}, // 2
    {{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}, // 3
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}, // 4
    {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}, // 5
    {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}, // 6
    {{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}} // 7
};

std::vector<uint32_t> indices = {
    0,  2,  1,    // 0-2-1
    0,  3,  2,    // 0-3-2
    4,  5,  6,    // 4-5-6
    4,  6,  7,    // 4-6-7
    2,  3,  7,    // 2-3-7
    2,  7,  6,    // 2-7-6
    1,  4,  0,    // 1-4-0
    1,  5,  4,    // 1-5-4
    0,  7,  3,    // 0-7-3
    0,  4,  7,    // 0-4-7
    1,  2,  6,    // 1-2-6
    1,  6,  5     // 1-6-5
};

int main() {

	try
	{
		Window mainWindow;
	    auto vk = std::make_shared<VulkanContext>(mainWindow.window());
	    Renderer renderer(mainWindow.window(), vk);

	    auto drawable = renderer.CreateDrawable(vertices, indices);
	    std::vector<Drawable> drawables = {std::move(drawable)};

		bool running = true;
        SDL_Event event;
        while (running)
        {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_EVENT_QUIT:
                        running = false;
                        break;
                    case SDL_EVENT_KEY_DOWN:
                        if (event.key.key == SDLK_ESCAPE)
                            running = false;
                        break;
                    default:
                        break;
                }
            }
            renderer.DrawFrame(drawables);
        }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}


}