#pragma once
#include "Image.h"

class DepthImage : public Image {
public:
    DepthImage(const std::shared_ptr<VulkanContext>& ctx, uint32_t width, uint32_t height);

private:
    void createDepthImage(uint32_t width, uint32_t height);
};
