#include "CommandPool.h"

#include <stdexcept>

CommandPool::CommandPool(const std::shared_ptr<VulkanContext>& vk)
    : m_vk(vk)
{
    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(m_vk->physicalDevice(), m_vk->surface());

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(m_vk->device(), &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS)
        throw std::runtime_error("failed to create command pool!");
}

CommandPool::~CommandPool()
{
    vkDestroyCommandPool(m_vk->device(), m_commandPool, nullptr);
}
