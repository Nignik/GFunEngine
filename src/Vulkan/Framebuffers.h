#pragma once
#include <vulkan/vulkan_core.h>

#include "RenderPass.h"
#include "VulkanContext.h"

class Framebuffers {
public:
    Framebuffers(const std::shared_ptr<VulkanContext>& vk, const RenderPass& renderPass, const Swapchain& swapchain);
    ~Framebuffers();

private:
    std::shared_ptr<VulkanContext> m_vk;
    std::vector<VkFramebuffer> m_framebuffers{};
};