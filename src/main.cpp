#include <iostream>

#include "Ecs.h"
#include "Vulkan/Renderer.h"
#include "Window.h"
#include "RendererSystem.h"

const std::vector<Vertex> vertices = {
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},  // 0: TL-front
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},  // 1: TR-front
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},  // 2: TR-back
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},  // 3: TL-back

    {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},  // 4: BL-front
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},  // 5: BR-front
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},  // 6: BR-back
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}   // 7: BL-back
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

Drawable createDrawable(std::shared_ptr<VulkanContext>& ctx, std::vector<Vertex> vertices, std::vector<uint32_t> indices)
{
    // Create vertex buffer
    VkDeviceSize vertexBufferSize = sizeof(vertices[0]) * vertices.size();
    VkDeviceSize indexBufferSize = sizeof(indices[0]) * indices.size();

    // Create vertex buffer
    auto vertexBuffer = std::make_shared<Buffer>(ctx, vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    Buffer vertexStagingBuffer(ctx, vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    vertexStagingBuffer.CopyData(vertices.data());
    vertexBuffer->CopyBuffer(ctx->GetGraphicsQueue(), ctx->GetCommandPool(), vertexStagingBuffer);

    auto indexBuffer = std::make_shared<Buffer>(ctx, indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    Buffer indexStagingBuffer(ctx, indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    indexStagingBuffer.CopyData(indices.data());
    indexBuffer->CopyBuffer(ctx->GetGraphicsQueue(), ctx->GetCommandPool(), indexStagingBuffer);

    return {std::move(vertices), std::move(indices), vertexBuffer, indexBuffer};
}

int main() {
    auto& ecs = Ecs::GetInstance();

	try
	{
		Window mainWindow;
	    auto vk = std::make_shared<VulkanContext>(mainWindow.window());

	    constexpr int N = 3;
	    glm::mat4 model = glm::mat4{1.f};
	    for (int i = 0; i < N; i++)
	    {
	        auto entt = ecs.CreateEntity();
	        auto drawable = createDrawable(vk, vertices, indices);
	        drawable.ubo = UniformBufferObject(model, glm::mat4{}, glm::mat4{});
	        ecs.AddComponents(entt, std::move(drawable));

	        model = glm::translate(model, glm::vec3(0.3f, 0.3f, 0.f));
	    }

	    Renderer renderer(mainWindow.window(), vk);
        ecs.AddSystem<RenderSystem>(renderer);

		bool running = true;
        SDL_Event event;
        while (running)
        {
            static auto startTime = std::chrono::high_resolution_clock::now();
            auto currentTime = std::chrono::high_resolution_clock::now();
            float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

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
            ecs.UpdateSystems(dt);
            vkDeviceWaitIdle(vk->GetDevice());
        }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}