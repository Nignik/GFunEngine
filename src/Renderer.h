#pragma once
#include "Vulkan/CommandPool.h"
#include "Vulkan/FrameBuffers.h"
#include "Vulkan/GraphicsPipeline.h"
#include "Vulkan/RenderPass.h"
#include "Vulkan/Swapchain.h"
#include "Vulkan/VulkanContext.h"

constexpr int MAX_FRAMES_IN_FLIGHT = 3;

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    void DrawFrame();

private:
	std::shared_ptr<VulkanContext> m_vk;
    Swapchain m_swapchain;
    RenderPass m_renderPass;
    PipelineLayout m_pipelineLayout;
    GraphicsPipeline m_graphicsPipeline;
    Framebuffers m_framebuffers;
    CommandPool m_commandPool;

    std::vector<VkSemaphore> m_imageAvailableSemaphores{};
    std::vector<VkSemaphore> m_renderFinishedSemaphores{};
    std::vector<VkFence> m_inFlightFences{};
};
