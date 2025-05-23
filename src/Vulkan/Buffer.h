#pragma once
#include <vulkan/vulkan_core.h>

#include "VulkanContext.h"

class Buffer {
public:
    Buffer(const std::shared_ptr<VulkanContext>& vk, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
    ~Buffer();

    void copyData(void* data);
    void copyBuffer(VkQueue graphicsQueue, VkCommandPool commandPool, Buffer& srcBuffer);

    [[nodiscard]] VkDeviceSize size() const;
    [[nodiscard]] VkBuffer get() const;

private:
    std::shared_ptr<VulkanContext> m_vk;
    VkBuffer m_buffer{};
    VkDeviceSize m_size{};
    VkDeviceMemory m_bufferMemory{};

	uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
};
