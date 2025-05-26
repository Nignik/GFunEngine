#include "FrameBuffers.h"

#include <stdexcept>

Framebuffers::Framebuffers(const std::shared_ptr<VulkanContext>& vk, const RenderPass& renderPass, const Swapchain& swapchain)
    : m_vk(vk)
{
    m_framebuffers.resize(swapchain.GetImageViews().size());

    for (size_t i = 0; i < swapchain.GetImageViews().size(); i++) {
        VkImageView attachments[] = {
            swapchain.GetImageView(i)
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass.renderPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = swapchain.GetExtent().width;
        framebufferInfo.height = swapchain.GetExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(m_vk->GetDevice(), &framebufferInfo, nullptr, &m_framebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

Framebuffers::~Framebuffers()
{
    for (auto& framebuffer : m_framebuffers)
        vkDestroyFramebuffer(m_vk->GetDevice(), framebuffer, nullptr);
}

