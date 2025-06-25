#include "PhysicsSystem.h"

#include <algorithm>
#include <print>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "../Collider.h"
#include "../Ecs.h"
#include "../Raycast.h"
#include "../Transform.h"
#include "../InputData.h"
#include "../Camera/Camera.h"
#include "../Components/Controller.h"

PhysicsSystem::PhysicsSystem() = default;

void PhysicsSystem::Update(float dt)
{
    auto& ecs = Ecs::GetInstance();

    Camera camera;
    Transform cameraTransform;
    bool castRay = false;

    for (auto& button : ecs.GetSingletonComponent<InputEvents>()->mouseButton)
        if (button.button == SDL_BUTTON_LEFT)
            castRay = true;

    ecs.Each<Camera, Transform, Controller, RayData>([&](Hori::Entity, Camera& cam, Transform& transform, Controller& controller, RayData& ray) {
        camera = cam;
        cameraTransform = transform;

        if (castRay && controller.mouseMode == MouseMode::GAME)
        {
            ray.active = true;
            ray.origin = cameraTransform.GetPosition();
            ray.dir = cameraTransform.GetForward();
            ray.hit = RayHit{};
        }
        else if (castRay && controller.mouseMode == MouseMode::EDITOR)
        {
            glm::ivec2 aspectRatio = cam.GetAspectRatio();
            float ndcX =  (2.0f * controller.mouseX) / static_cast<float>(aspectRatio.x) - 1.f;
            float ndcY =  1.f - (2.0f * controller.mouseY) / static_cast<float>(aspectRatio.y);

            glm::vec4 clipNear = glm::vec4(ndcX, ndcY, -1.0f, 1.0f);
            glm::vec4 clipFar  = glm::vec4(ndcX, ndcY,  1.0f, 1.0f);

            glm::mat4 invViewProj = glm::inverse(camera.GetPerspectiveProjection() * camera.GetView(cameraTransform.GetModel()));

            glm::vec4 pNear = invViewProj * clipNear;
            pNear /= pNear.w;

            glm::vec4 pFar  = invViewProj * clipFar;
            pFar  /= pFar.w;

            ray.active = true;
            ray.origin = cameraTransform.GetPosition();
            ray.dir = glm::normalize(glm::vec3(pFar) - ray.origin);
            ray.hit = RayHit{};
        }
    });

    ecs.Each<RayData>([&ecs](Hori::Entity, RayData& ray) {
        if (!ray.active)
            return;

        ecs.Each<SphereCollider>([&ecs, &ray](Hori::Entity& e, SphereCollider& collider) {
            constexpr float epsilon = 1e-4f;

            glm::vec3 pos = ecs.GetComponent<Transform>(e)->GetPosition();
            glm::vec3 oc = ray.origin - pos;
            float b = glm::dot(oc, ray.dir);
            float c = glm::length2(oc) - collider.radius*collider.radius;
            float disc = b*b - c;

            if (disc < 0.0f)
                return;

            float t = -b - std::sqrt(disc);
            if (t < epsilon)
                t = -b + std::sqrt(disc);
            if (t < epsilon)
                return;

            ray.hit = ray.hit.dist < glm::length(oc) ? RayHit{e, pos, glm::length(oc)} : ray.hit;
        });

        if (ray.hit.e.Valid())
            std::print("Ray had hit an entity: {}\n", ray.hit.e.id);

        ray.hit.e.id = 0;
        ray.active = false;
    });
}
