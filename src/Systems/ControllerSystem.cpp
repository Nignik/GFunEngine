#include "ControllerSystem.h"

#include <SDL3/SDL.h>

#include "../Components/Controller.h"

void ControllerSystem::Update(float dt)
{
    auto& ecs = Ecs::GetInstance();

    ecs.Each<Controller>([](Hori::Entity, Controller& controller) {
        glm::vec3 dir{};
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
               switch (event.type) {
                   case SDL_EVENT_KEY_DOWN:
                       if (event.key.key == SDLK_W)
                           dir.z += 1.f;
                       else if (event.key.key == SDLK_S)
                           dir.z -= 1.f;
                       else if (event.key.key == SDLK_D)
                           dir.x += 1.f;
                       else if (event.key.key == SDLK_A)
                           dir.x -= 1.f;
                       break;
                   default:
                       break;
               }
           }
        controller.direction = dir;
    });
}
