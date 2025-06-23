#include "Window.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>
#include <SDL3/SDL_vulkan.h>
#include "Vulkan/Swapchain.h"
#include "Vulkan/VulkanContext.h"

Window::Window()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error("Failed to initialize SDL");

    m_window = SDL_CreateWindow("GFunEngine", 1600, 900, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
    if (!m_window)
        throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());

    SDL_AddEventWatch(resizingEventWatcher, this);
    SDL_SetWindowRelativeMouseMode(m_window, true);
    SDL_CaptureMouse(true);
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

SDL_Window* Window::window()
{
    return m_window;
}

/*
void Window::recreateSwapChain()
{
    while (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED) {
        SDL_Event event;
        SDL_WaitEvent(&event);
    }
    vkDeviceWaitIdle(m_device);

    cleanupSwapChain();

    createSwapChain();
    createImageViews();
    createFramebuffers();
}
*/

bool Window::resizingEventWatcher(void* data, SDL_Event* event)
{
    if (event->type == SDL_EVENT_WINDOW_RESIZED)
    {
        SDL_Window* sdlWindow = SDL_GetWindowFromID(event->window.windowID);
        auto window = static_cast<Window*>(data);
//        if (sdlWindow == window->m_window)
//            window->recreateSwapChain();
    }
    return false;
}