#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>

#include "VulkanUtils.h"
#include "VulkanContext.h"
#include "Swapchain.h"

class CommandPool {
public:
    CommandPool(const std::shared_ptr<VulkanContext>& vk);
    ~CommandPool();

private:
    std::shared_ptr<VulkanContext> m_vk;
    VkCommandPool m_commandPool{};

    void createCommandBuffer();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
};
