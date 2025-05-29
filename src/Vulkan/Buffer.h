#pragma once
#include <vulkan/vulkan_core.h>
#include <glm/glm.hpp>

#include "VulkanContext.h"

class Buffer {
public:
    Buffer(const std::shared_ptr<VulkanContext>& ctx, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
    ~Buffer();

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;

    void CopyData(void* data);
    void CopyBuffer(VkQueue graphicsQueue, VkCommandPool commandPool, Buffer& srcBuffer);

    [[nodiscard]] VkDeviceSize GetSize() const;
    [[nodiscard]] VkBuffer GetVkBuffer() const;
    [[nodiscard]] void* GetMappedBuffer() const;

    void Map();

private:
    std::shared_ptr<VulkanContext> m_ctx;
    VkBuffer m_buffer{};
    VkDeviceSize m_size{};
    VkDeviceMemory m_memory{};
    void* m_mapped = nullptr;

private:
    void cleanup() noexcept;
    void moveFrom(Buffer&& other) noexcept;
};
