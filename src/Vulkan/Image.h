#pragma once
#include <filesystem>
#include <vulkan/vulkan_core.h>

#include <memory>
#include <vulkan/vulkan_core.h>

#include "VulkanContext.h"

class Image {
public:
    Image(const std::shared_ptr<VulkanContext>& ctx);

    ~Image();

    [[nodiscard]] VkImage GetImage() const;
    [[nodiscard]] VkSampler GetSampler() const;

    Image(const Image& other) = delete;
    Image(Image&& other) noexcept = delete;
    Image& operator=(const Image& other) = delete;
    Image& operator=(Image&& other) noexcept = delete;

    void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

protected:
    std::shared_ptr<VulkanContext> m_ctx;

    VkImage m_image{};
    VkDeviceMemory m_memory{};
    VkSampler m_sampler{};

protected:
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);

    void createSampler();
};