#pragma once
#include "Vulkan/Buffer.h"
#include "Vulkan/GraphicsPipeline.h"

struct Drawable {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::shared_ptr<Buffer> vertexBuffer;
    std::shared_ptr<Buffer> indexBuffer;
};
