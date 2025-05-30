#pragma once

#include <vulkan/vulkan_core.h>

#include "VulkanUtils.h"
#include "Buffer.h"

class TextureImage {
public:
    explicit TextureImage(const std::shared_ptr<VulkanContext>& ctx, const std::filesystem::path& path);
    ~TextureImage();

    [[nodiscard]] VkImage GetImage() const;

    void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

private:
    std::shared_ptr<VulkanContext> m_ctx;

    VkImage m_textureImage{};
    VkDeviceMemory m_memory{};
    VkImageView m_view{};
    VkSampler m_sampler{};

private:
    void createTextureImage(const std::filesystem::path& path);
    void createSampler();
};