#include <iostream>
#include "Ecs.h"
#include "Renderer.h"
#include "Window.h"

int main() {

	try
	{
		Window mainWindow;
	    Renderer renderer(mainWindow.window());

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
        }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}


}