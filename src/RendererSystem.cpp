#include "RendererSystem.h"

RenderSystem::RenderSystem(Renderer& renderer)
    : m_renderer(&renderer)
{}

void RenderSystem::Update(float dt)
{
    auto& ecs = Ecs::GetInstance();

    std::vector<Drawable> drawables;
    ecs.Each<Drawable>([&drawables](Hori::Entity, Drawable& drawable) {
        drawables.push_back(drawable);
    });

    m_renderer->DrawFrame(drawables);
}
