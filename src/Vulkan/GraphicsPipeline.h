#pragma once

#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <vulkan/vulkan_core.h>

#include "Buffer.h"
#include "RenderPass.h"
#include "VulkanContext.h"

constexpr int MAX_FRAMES_IN_FLIGHT = 3;

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);
        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

class GraphicsPipeline {
public:
    GraphicsPipeline(const std::shared_ptr<VulkanContext>& vk, VkRenderPass renderPass);
    ~GraphicsPipeline();

    void UpdateUniformBuffer(VkExtent2D extent, uint32_t currentImage);

    [[nodiscard]] VkPipeline GetGraphicsPipeline() const;
    [[nodiscard]] VkDescriptorPool GetDescriptorPool() const;
    [[nodiscard]] VkDescriptorSetLayout GetDescriptorSetLayout() const;
    [[nodiscard]] VkPipelineLayout GetPipelineLayout() const;
    [[nodiscard]] std::vector<std::shared_ptr<Buffer>> GetUniformBuffers() const;
    [[nodiscard]] std::vector<VkDescriptorSet> GetDescriptorSets() const;

private:
    std::shared_ptr<VulkanContext> m_vk;
    VkPipeline m_graphicsPipeline{};
    VkDescriptorPool m_descriptorPool{};
    VkDescriptorSetLayout m_descriptorSetLayout{};
    VkPipelineLayout m_pipelineLayout{};

    std::vector<std::shared_ptr<Buffer>> m_uniformBuffers;
    std::vector<VkDescriptorSet> m_descriptorSets{};

    void createDescriptorPool();
    void createDescriptorSetLayout();
    void createPipelineLayout();
    void createUniformBuffers();
    void createDescriptorSets();
    void createGraphicsPipeline(VkRenderPass renderPass);
    VkShaderModule createShaderModule(const std::vector<char>& code);
};