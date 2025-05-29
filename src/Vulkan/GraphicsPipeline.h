#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <vulkan/vulkan_core.h>

#include "../Drawable.h"
#include "Buffer.h"
#include "VulkanContext.h"

constexpr int MAX_FRAMES_IN_FLIGHT = 3;

class GraphicsPipeline {
public:
    GraphicsPipeline(const std::shared_ptr<VulkanContext>& ctx, VkRenderPass renderPass, size_t drawablesCount);
    ~GraphicsPipeline();

    void UpdateUniformBuffers(VkExtent2D extent, uint32_t currentImage, std::vector<Drawable>& drawables);

    [[nodiscard]] VkPipeline GetGraphicsPipeline() const;
    [[nodiscard]] VkDescriptorPool GetDescriptorPool() const;
    [[nodiscard]] VkDescriptorSetLayout GetDescriptorSetLayout() const;
    [[nodiscard]] VkPipelineLayout GetPipelineLayout() const;
    [[nodiscard]] std::vector<std::shared_ptr<Buffer>> GetUniformBuffers() const;
    [[nodiscard]] VkDescriptorSet GetDescriptorSet(uint32_t currentFrame, uint32_t currentDrawable) const;
    [[nodiscard]] std::vector<VkDescriptorSet> GetDescriptorSets() const;

private:
    std::shared_ptr<VulkanContext> m_ctx;
    VkPipeline m_graphicsPipeline{};
    VkDescriptorPool m_descriptorPool{};
    VkDescriptorSetLayout m_descriptorSetLayout{};
    VkPipelineLayout m_pipelineLayout{};

    std::vector<std::shared_ptr<Buffer>> m_uniformBuffers;
    std::vector<VkDescriptorSet> m_descriptorSets;

    size_t m_drawablesCount;

private:
    void createDescriptorPool();
    VkDescriptorSetLayoutBinding createDescriptorSetLayoutBinding(VkDescriptorType type, VkShaderStageFlags stageFlags, uint32_t binding);
    VkWriteDescriptorSet createWriteDescriptorBuffer(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding);
    void createDescriptorSetLayout();
    void createPipelineLayout();
    void createUniformBuffers(size_t drawablesCount);
    void createDescriptorSets(size_t drawablesCount);
    void createGraphicsPipeline(VkRenderPass renderPass);
    VkShaderModule createShaderModule(const std::vector<char>& code);

};