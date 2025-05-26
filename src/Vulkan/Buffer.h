#pragma once
#include <vulkan/vulkan_core.h>
#include <glm/glm.hpp>

#include "VulkanContext.h"

class Buffer {
public:
    Buffer(const std::shared_ptr<VulkanContext>& vk, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
    ~Buffer();

    Buffer(const Buffer&)            = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;

    void copyData(void* data);
    void copyBuffer(VkQueue graphicsQueue, VkCommandPool commandPool, Buffer& srcBuffer);

    [[nodiscard]] VkDeviceSize size() const;
    [[nodiscard]] VkBuffer get() const;
    [[nodiscard]] void* GetMappedBuffer() const;

    void Map();

private:
    std::shared_ptr<VulkanContext> m_vk;
    VkBuffer m_buffer{};
    VkDeviceSize m_size{};
    VkDeviceMemory m_memory{};
    void* m_mapped = nullptr;

    void cleanup() noexcept;
    void moveFrom(Buffer&& other) noexcept;
	uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
};
