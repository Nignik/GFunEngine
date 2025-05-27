#pragma once

#include <System.h>

#include "GraphicsPipeline.h"
#include "Swapchain.h"
#include "VulkanContext.h"
#include "../Drawable.h"



class Renderer {
public:
    Renderer(SDL_Window* window, const std::shared_ptr<VulkanContext>& ctx);
    ~Renderer();

    void DrawFrame(std::vector<Drawable>& drawables);
    [[nodiscard]] Drawable CreateDrawable(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) const;

private:
    SDL_Window* m_window;

	std::shared_ptr<VulkanContext> m_ctx;
    Swapchain m_swapchain;
    GraphicsPipeline m_gfx;

    std::vector<VkCommandBuffer> m_commandBuffers{};

    std::vector<VkSemaphore> m_imageAvailableSemaphores{};
    std::vector<VkSemaphore> m_renderFinishedSemaphores{};
    std::vector<VkFence> m_inFlightFences{};

    uint32_t m_currentFrame = 0;

    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, std::vector<Drawable>& drawables);
};
