#include <iostream>

#include "Ecs.h"
#include "Vulkan/Renderer.h"
#include "Window.h"
#include "Camera/Camera.h"
#include "Systems/RendererSystem.h"
#include "Components/Controller.h"
#include "Systems/ControllerSystem.h"

const std::vector<Vertex> vertices = {
/* +Z (front)  */ {{-0.5f,-0.5f, 0.5f},{1,0,0},{0,0}}, // 0
                   {{ 0.5f,-0.5f, 0.5f},{0,1,0},{1,0}}, // 1
                   {{ 0.5f, 0.5f, 0.5f},{0,0,1},{1,1}}, // 2
                   {{-0.5f, 0.5f, 0.5f},{1,1,1},{0,1}}, // 3
/* –Z (back)   */ {{ 0.5f,-0.5f,-0.5f},{1,0,0},{0,0}}, // 4
                   {{-0.5f,-0.5f,-0.5f},{0,1,0},{1,0}}, // 5
                   {{-0.5f, 0.5f,-0.5f},{0,0,1},{1,1}}, // 6
                   {{ 0.5f, 0.5f,-0.5f},{1,1,1},{0,1}}, // 7
/* –X (left)   */ {{-0.5f,-0.5f,-0.5f},{1,0,0},{0,0}}, // 8
                   {{-0.5f,-0.5f, 0.5f},{0,1,0},{1,0}}, // 9
                   {{-0.5f, 0.5f, 0.5f},{0,0,1},{1,1}}, // 10
                   {{-0.5f, 0.5f,-0.5f},{1,1,1},{0,1}}, // 11
/* +X (right)  */ {{ 0.5f,-0.5f, 0.5f},{1,0,0},{0,0}}, // 12
                   {{ 0.5f,-0.5f,-0.5f},{0,1,0},{1,0}}, // 13
                   {{ 0.5f, 0.5f,-0.5f},{0,0,1},{1,1}}, // 14
                   {{ 0.5f, 0.5f, 0.5f},{1,1,1},{0,1}}, // 15
/* +Y (top)    */ {{-0.5f, 0.5f, 0.5f},{1,0,0},{0,0}}, // 16
                   {{ 0.5f, 0.5f, 0.5f},{0,1,0},{1,0}}, // 17
                   {{ 0.5f, 0.5f,-0.5f},{0,0,1},{1,1}}, // 18
                   {{-0.5f, 0.5f,-0.5f},{1,1,1},{0,1}}, // 19
/* –Y (bottom) */ {{-0.5f,-0.5f,-0.5f},{1,0,0},{0,0}}, // 20
                   {{ 0.5f,-0.5f,-0.5f},{0,1,0},{1,0}}, // 21
                   {{ 0.5f,-0.5f, 0.5f},{0,0,1},{1,1}}, // 22
                   {{-0.5f,-0.5f, 0.5f},{1,1,1},{0,1}}  // 23
};

/* Two CCW triangles per face */
const std::vector<uint32_t> indices = {
    0,1,2,  2,3,0,       // +Z
    4,5,6,  6,7,4,       // –Z
    8,9,10, 10,11,8,     // –X
    12,13,14, 14,15,12,  // +X
    16,17,18, 18,19,16,  // +Y
    20,21,22, 22,23,20   // –Y
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

		constexpr int N = 1;
		glm::mat4 model = glm::mat4{1.f};
		for (int i = 0; i < N; i++)
		{
			auto entt = ecs.CreateEntity();
			auto drawable = createDrawable(vk, vertices, indices);
			drawable.ubo = UniformBufferObject(model, glm::mat4{}, glm::mat4{});
			drawable.transform = Transform({0.0f, 0.0f, 0.0f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f});
			ecs.AddComponents(entt, std::move(drawable));
		}

		Hori::Entity camera = ecs.CreateEntity();
		Transform camTrans{{0.f, -10.f, -10.f}, glm::vec3{0.f}, glm::vec3{1.f}};
		camTrans.LookAt({0.f, 0.f, 0.f});
		ecs.AddComponents(camera, Camera{});
		ecs.AddComponents(camera, std::move(camTrans));

		Renderer renderer(mainWindow.window(), vk);
		ecs.AddSystem<RenderSystem>(renderer);

		auto prevTime = std::chrono::high_resolution_clock::now();
		bool running = true;
        SDL_Event event;
        while (running)
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - prevTime).count();

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
        	prevTime = currentTime;
        }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}