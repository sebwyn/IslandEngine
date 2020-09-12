#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

#include "platform/window/Window.hpp"
#include "platform/vulkan/Renderer.hpp"

int main() 
{
    int width = 800;
    int height = 600;
    Window myWindow(width, height, "A Vulkan window");

    Renderer::init(myWindow.getGLFWWindow());
    glfwSetFramebufferSizeCallback(myWindow.getGLFWWindow(), Renderer::framebufferResizeCallback);
    
    while(!myWindow.shouldClose()){
        Renderer::draw();
        myWindow.update();
    }

    Renderer::destroy();
}
