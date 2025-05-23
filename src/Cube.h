#pragma once

#include "Vulkan/GraphicsPipeline.h"
#include "Vulkan/Buffer.h"

class Cube {
public:
    Cube(VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

private:
    std::vector<Vertex> m_vertices{};
    std::vector<uint32_t> m_indices{};

    std::shared_ptr<Buffer> m_vertexBuffer{};
    std::shared_ptr<Buffer> m_indexBuffer{};
};