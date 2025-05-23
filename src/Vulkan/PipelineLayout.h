#pragma once
#include <vulkan/vulkan_core.h>

#include "VulkanContext.h"

class PipelineLayout {
public:
    PipelineLayout(const std::shared_ptr<VulkanContext>& vk);
    ~PipelineLayout();

    VkPipelineLayout pipelineLayout() const;

private:
    std::shared_ptr<VulkanContext> m_vk;

    VkDescriptorSetLayout m_descriptorSetLayout{};
    VkPipelineLayout m_pipelineLayout{};

    void createDescriptorPool();
    void createDescriptorSets();
};
