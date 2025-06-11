#pragma once

#include <vulkan/vulkan_core.h>

#include "VulkanUtils.h"
#include "Buffer.h"
#include "Image.h"

class TextureImage : public Image {
public:
    explicit TextureImage(const std::shared_ptr<VulkanContext>& ctx, const std::filesystem::path& path);

private:
    void createTextureImage(const std::filesystem::path& path);
};
