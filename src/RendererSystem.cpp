#include "RendererSystem.h"

RenderSystem::RenderSystem(Renderer& renderer)
    : m_renderer(&renderer)
{}

void RenderSystem::Update(float dt)
{
    auto& ecs = Ecs::GetInstance();

    static std::vector<Drawable> drawables;
    drawables.clear();
    ecs.Each<Drawable>([](Hori::Entity, Drawable& drawable) {
        drawables.push_back(drawable);
    });

    m_renderer->DrawFrame(drawables);
}
