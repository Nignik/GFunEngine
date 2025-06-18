#include "RendererSystem.h"
#include "../Camera/Camera.h"

RenderSystem::RenderSystem(Renderer& renderer)
    : m_renderer(&renderer)
{}

void RenderSystem::Update(float dt)
{
    auto& ecs = Ecs::GetInstance();

    Camera camera;
    Transform transform;
    ecs.Each<Camera, Transform>([&camera, &transform](Hori::Entity e, Camera cam, Transform trans) {
        camera = cam;
        transform = trans;
    });

    static std::vector<Drawable> drawables;
    drawables.clear();
    // TODO: iterate over drawables with transform
    ecs.Each<Drawable>([dt, &camera, &transform](Hori::Entity, Drawable& drawable) {
        drawable.transform.Rotate({1.f, 1.f, 0.f}, dt);

        drawable.ubo.model = drawable.transform.GetModel();
        drawable.ubo.view = camera.GetView(transform.GetModel());
        drawable.ubo.proj = camera.GetPerspectiveProjection();
        drawables.push_back(drawable);
    });

    m_renderer->DrawFrame(drawables);
}
