#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>

#include "VulkanContext.h"
#include "VulkanUtils.h"

class Swapchain {
public:
	Swapchain(const std::shared_ptr<VulkanContext>& vk, SDL_Window* window);
	~Swapchain();

	[[nodiscard]] VkFormat imageFormat() const;
	[[nodiscard]] std::vector<VkImageView> imageViews() const;
	[[nodiscard]] std::vector<VkFramebuffer> framebuffers() const;
	[[nodiscard]] VkExtent2D extent() const;

	[[nodiscard]] VkImageView GetImageView(size_t idx) const;
private:
	std::shared_ptr<VulkanContext> m_vk;

    VkSwapchainKHR m_swapchain{};

    std::vector<VkImage> m_images{};
    std::vector<VkImageView> m_imageViews{};

    VkFormat m_imageFormat{};
    VkExtent2D m_extent{};
    uint32_t m_currentFrame = 0;
    bool m_resized = false;

	void recreateSwapChain();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, SDL_Window* window);
};
