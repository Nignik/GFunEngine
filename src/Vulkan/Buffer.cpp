#include "Buffer.h"

#include <stdexcept>

Buffer::Buffer(const std::shared_ptr<VulkanContext>& vk, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
    : m_vk(vk)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(m_vk->device(), &bufferInfo, nullptr, &m_buffer) != VK_SUCCESS)
        throw std::runtime_error("failed to create buffer!");

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_vk->device(), m_buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(m_vk->physicalDevice(), memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(m_vk->device(), &allocInfo, nullptr, &m_bufferMemory) != VK_SUCCESS)
        throw std::runtime_error("failed to allocate buffer memory!");

    vkBindBufferMemory(m_vk->device(), m_buffer, m_bufferMemory, 0);
}

Buffer::~Buffer()
{
    vkDestroyBuffer(m_vk->device(), m_buffer, nullptr);
    vkFreeMemory(m_vk->device(), m_bufferMemory, nullptr);
}

void Buffer::copyData(void* data)
{
    void* vkData;
    vkMapMemory(m_vk->device(), m_bufferMemory, 0, m_size, 0, &vkData);
    memcpy(vkData, data, (size_t) m_size);
    vkUnmapMemory(m_vk->device(), m_bufferMemory);
}

VkDeviceSize Buffer::size() const
{
    return m_size;
}

VkBuffer Buffer::get() const
{
    return m_buffer;
}

void Buffer::copyBuffer(VkQueue graphicsQueue, VkCommandPool commandPool, Buffer& srcBuffer)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(m_vk->device(), &allocInfo, &commandBuffer);

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

    vkFreeCommandBuffers(m_vk->device(), commandPool, 1, &commandBuffer);
}

uint32_t Buffer::findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
        if (typeFilter & (typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
            return i;

    throw std::runtime_error("failed to find suitable memory type!");
}
