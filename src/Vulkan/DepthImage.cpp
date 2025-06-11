#include "DepthImage.h"

DepthImage::DepthImage(const std::shared_ptr<VulkanContext>& ctx, uint32_t width, uint32_t height)
    : Image(ctx)
{
    createDepthImage(width, height);
}

void DepthImage::createDepthImage(uint32_t width, uint32_t height)
{
    createImage(width, height, VK_FORMAT_D32_SFLOAT, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
}


