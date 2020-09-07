#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

#include "Socket.hpp"

int main() 
{
    Socket socket;
    unsigned short port = 1337;

    if(!socket.open(port)){
        std::cout << "Failed to make socket" << std::endl;
        return 1;
    }

    char message[] = "Hello, World!";
    socket.send(Address(127,0,0,1, port), message, sizeof(message));
    
    while(true){
        Address sender;
        char buffer[256];
        int bytesRead = socket.receive(sender, buffer, sizeof(buffer));

        if(bytesRead <= 0){
        //    std::cout << "Didn't receive message" << std::endl;
        } else {
            std::cout << "Received: " << std::string(buffer, bytesRead) 
                      << " from localhost" << std::endl;
            break;
        }
    }
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
