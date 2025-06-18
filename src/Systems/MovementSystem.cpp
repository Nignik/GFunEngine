#include "MovementSystem.h"

#include "../Ecs.h"
#include "../Components/Controller.h"
#include "../Transform.h"


MovementSystem::MovementSystem()
{

}

void MovementSystem::Update(float dt)
{
    auto& ecs = Ecs::GetInstance();
/*    ecs.Each<Controller, Transform>([dt](Hori::Entity, Controller& controller, Transform& transform) {
        glm::vec3 velocity = transform.GetRotation() * controller.direction * controller.speed * dt;
        transform.Translate(velocity);
    });*/
}
