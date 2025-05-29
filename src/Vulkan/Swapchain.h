#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>

#include "VulkanContext.h"
#include "VulkanUtils.h"
#include "TextureImage.h"

class Swapchain {
public:
	Swapchain(const std::shared_ptr<VulkanContext>& ctx, SDL_Window* window);
	~Swapchain();

	void RecreateSwapchain();

	[[nodiscard]] VkSwapchainKHR GetSwapchain() const;
	[[nodiscard]] VkRenderPass GetRenderPass() const;
	[[nodiscard]] VkFormat GetImageFormat() const;
	[[nodiscard]] std::vector<VkImageView> GetImageViews() const;
	[[nodiscard]] std::vector<VkFramebuffer> GetFramebuffers() const;
	[[nodiscard]] VkExtent2D GetExtent() const;
	[[nodiscard]] bool IsResized() const;
	[[nodiscard]] VkImageView GetImageView(size_t idx) const;

	void SetResized(bool resized);

private:
	std::shared_ptr<VulkanContext> m_ctx;
	SDL_Window* m_window;

    VkSwapchainKHR m_swapchain{};
	VkRenderPass m_renderPass{};

    std::vector<VkImage> m_images;
    std::vector<VkImageView> m_imageViews;
	std::vector<VkFramebuffer> m_framebuffers;

	VkImage m_depthImage{};
	VkDeviceMemory depthImageMemory{};
	VkImageView depthImageView{};

    VkFormat m_imageFormat{};
    VkExtent2D m_extent;
    uint32_t m_currentFrame = 0;
    bool m_resized = false;

private:
	void createSwapchain();
	void createRenderPass();
	void createImageViews();
	void createFramebuffers();
	void createDepthBuffer();

	void cleanupSwapchain();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, SDL_Window* window);
};
