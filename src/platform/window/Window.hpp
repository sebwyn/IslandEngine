#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

/*
 * A glfw window initialized for vulkan
 */
class Window {
public:
    Window(int width, int height, std::string title);
    ~Window();

    GLFWwindow* getGLFWWindow() const { return m_window; }
    bool shouldClose();

    void update();
private:
    GLFWwindow* m_window;
};
