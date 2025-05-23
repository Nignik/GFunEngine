#pragma once
#include <vulkan/vulkan_core.h>

#include "Swapchain.h"
#include "VulkanContext.h"

class RenderPass {
public:
    RenderPass(const std::shared_ptr<VulkanContext>& vk, const Swapchain& swapchain);
    ~RenderPass();

    [[nodiscard]] VkRenderPass renderPass() const;

private:
    std::shared_ptr<VulkanContext> m_vk;
	VkRenderPass m_renderPass{};
};
