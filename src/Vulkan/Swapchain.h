#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>

#include "VulkanContext.h"
#include "VulkanUtils.h"
#include "TextureImage.h"
#include "Image.h"
#include "DepthImage.h"

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
	[[nodiscard]] VkImage GetTextureImage() const;
	[[nodiscard]] VkImageView GetTextureImageView() const;
	[[nodiscard]] VkSampler GetTextureImageSampler() const;

	void SetResized(bool resized);

	Swapchain(Swapchain&& other) = delete;
	Swapchain& operator=(Swapchain&& other) = delete;
	Swapchain(const Swapchain&) = delete;
	Swapchain& operator=(const Swapchain&) = delete;

private:
	std::shared_ptr<VulkanContext> m_ctx;
	SDL_Window* m_window;

    VkSwapchainKHR m_swapchain{};
	VkRenderPass m_renderPass{};

    std::vector<VkImage> m_images;
    std::vector<VkImageView> m_imageViews;
	//std::vector<TextureImage> m_textureImages;
	//std::vector<VkImageView> m_textureImageViews;
	std::optional<TextureImage> m_textureImage;
	VkImageView m_textureImageView;

	std::optional<DepthImage> m_depthImage;
	VkImageView m_depthImageView;

	std::vector<VkFramebuffer> m_framebuffers;

    VkFormat m_imageFormat{};
    VkExtent2D m_extent;
    uint32_t m_currentFrame;
    bool m_resized = false;

private:
	void createSwapchain();
	void createRenderPass();
	void createImageViews();
	void createFramebuffers();
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

	void cleanupSwapchain();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, SDL_Window* window);
};
