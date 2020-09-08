#include "Window.hpp"

Window::Window(int width, int height, std::string title)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::update()
{
    glfwPollEvents();
}
