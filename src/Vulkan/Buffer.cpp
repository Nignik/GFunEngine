#include "Buffer.h"

#include <stdexcept>

#include "VulkanUtils.h"

Buffer::Buffer(const std::shared_ptr<VulkanContext>& ctx, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
    : m_ctx(ctx),
    m_size(size)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(m_ctx->GetDevice(), &bufferInfo, nullptr, &m_buffer) != VK_SUCCESS)
        throw std::runtime_error("failed to create buffer!");

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_ctx->GetDevice(), m_buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(m_ctx->GetPhysicalDevice(), memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(m_ctx->GetDevice(), &allocInfo, nullptr, &m_memory) != VK_SUCCESS)
        throw std::runtime_error("failed to allocate buffer memory!");

    vkBindBufferMemory(m_ctx->GetDevice(), m_buffer, m_memory, 0);
}

Buffer::~Buffer()
{
    cleanup();
}

Buffer::Buffer(Buffer&& other) noexcept
{
    moveFrom(std::move(other));
}

Buffer& Buffer::operator=(Buffer&& other) noexcept
{
    if (this != &other)
    {
        cleanup();
        moveFrom(std::move(other));
    }
    return *this;
}

void Buffer::CopyData(void* data)
{
    void* vkData;
    vkMapMemory(m_ctx->GetDevice(), m_memory, 0, m_size, 0, &vkData);
    memcpy(vkData, data, (size_t) m_size);
    vkUnmapMemory(m_ctx->GetDevice(), m_memory);
}

VkDeviceSize Buffer::GetSize() const
{
    return m_size;
}

VkBuffer Buffer::GetVkBuffer() const
{
    return m_buffer;
}

void* Buffer::GetMappedBuffer() const
{
    return m_mapped;
}

void Buffer::Map()
{
    vkMapMemory(m_ctx->GetDevice(), m_memory, 0, m_size, 0, &m_mapped);
}

void Buffer::CopyBuffer(VkQueue graphicsQueue, VkCommandPool commandPool, Buffer& srcBuffer)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(m_ctx->GetDevice(), &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0; // Optional
    copyRegion.dstOffset = 0; // Optional
    copyRegion.size = m_size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer.m_buffer, m_buffer, 1, &copyRegion);
    vkEndCommandBuffer(commandBuffer);
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);

    vkFreeCommandBuffers(m_ctx->GetDevice(), commandPool, 1, &commandBuffer);
}

void Buffer::cleanup() noexcept
{
    if (!m_ctx) return;
    VkDevice dev = m_ctx->GetDevice();

    if (m_mapped) {
        vkUnmapMemory(dev, m_memory);
        m_mapped = nullptr;
    }
    if (m_buffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(dev, m_buffer, nullptr);
        m_buffer = VK_NULL_HANDLE;
    }
    if (m_memory != VK_NULL_HANDLE) {
        vkFreeMemory(dev, m_memory, nullptr);
        m_memory = VK_NULL_HANDLE;
    }
}

void Buffer::moveFrom(Buffer&& other) noexcept
{
    m_ctx           = std::move(other.m_ctx);
    m_buffer       = std::exchange(other.m_buffer,       VK_NULL_HANDLE);
    m_memory = std::exchange(other.m_memory, VK_NULL_HANDLE);
    m_size         = other.m_size;
    m_mapped       = other.m_mapped;
    other.m_mapped = nullptr;
}

