#include "Cube.h"

Cube::Cube(VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
    : m_vertices(vertices),
    m_indices(indices)
{
    /*
    // Create vertex buffer
    VkDeviceSize vertexBufferSize = sizeof(m_vertices[0]) * m_vertices.size();
    VkDeviceSize indexBufferSize = sizeof(m_indices[0]) * m_indices.size();

    // Create vertex buffer
    m_vertexBuffer = std::make_shared<Buffer>(device, vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    Buffer vertexStagingBuffer(device, vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    vertexStagingBuffer.copyData(m_vertices.data());
    m_vertexBuffer->copyBuffer(graphicsQueue, commandPool, vertexStagingBuffer);

    m_indexBuffer = std::make_shared<Buffer>(device, indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    Buffer indexStagingBuffer(device, indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    indexStagingBuffer.copyData(m_vertices.data());
    m_indexBuffer->copyBuffer(graphicsQueue, commandPool, indexStagingBuffer);
    */
}
