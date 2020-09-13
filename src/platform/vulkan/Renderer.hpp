#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

#include <fstream>
#include <string>
#include <optional>
#include <vector>
#include <array>

/* TODO: think about how to organize all of the init vulkan code
 * TODO: add our own callback for vulkan validation errors
 * TODO: use the custom IslandEngine event system for resize handling instead of
 * direct glfw calls
 *
 * this class also assumes that glfw is being used
 */
class Renderer {
public:
    static void init(GLFWwindow* window); 
    static void destroy();

    static void draw();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
private:

    struct Vertex {
        glm::vec2 pos;
        glm::vec3 color;

        static VkVertexInputBindingDescription getBindindDescription()
        {
            VkVertexInputBindingDescription bindingDescription;

            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            return attributeDescriptions;
        }
    };

    static std::vector<Vertex> m_vertices;

    //Lots of vulkan shit I barely understand
    static std::string m_vertPath;
    static std::string m_fragPath;

    static int m_maxFramesInFlight;

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };


    //vulkan initialization
    static void initVulkan();
    static void destroyVulkan();
    static void destroySwapChain();

    static bool checkValidationLayerSupport();

    static void createInstance();
    //used for windowed rendering(relies on GLFW)
    static void createSurface();
    static void pickPhysicalDevice();
    static void createLogicalDevice();
    static void createSwapChain();
    static void createImageViews();
    static VkShaderModule createShaderModule(const std::vector<char>& code);
    static void createRenderPass();
    static void createGraphicsPipeline();
    static void createFramebuffers();
    static void createCommandPool();
    static void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& memory);
    static void createVertexBuffer();
    static void createCommandBuffers();
    static void createSyncObjects();

    static void recreateSwapChain();

    static int rateDeviceSuitability(VkPhysicalDevice device);
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    static bool enableValidationLayers;

    static GLFWwindow* m_glfwWindow;

    static std::vector<const char*> m_validationLayers, m_deviceExtensions;
    static VkInstance m_instance;
    static VkSurfaceKHR m_surface;
    static VkPhysicalDevice m_physicalDevice;
    static VkDevice m_device;

    static VkSwapchainKHR m_swapChain;

    static std::vector<VkImage> m_swapChainImages;
    static VkFormat m_swapChainImageFormat;
    static VkExtent2D m_swapChainExtent;

    static std::vector<VkImageView> m_swapChainImageViews;
    static std::vector<VkFramebuffer> m_swapChainFramebuffers;

    static VkRenderPass m_renderPass;
    static VkPipelineLayout m_pipelineLayout;
    static VkPipeline m_graphicsPipeline;

    static VkCommandPool m_commandPool;
    static std::vector<VkCommandBuffer> m_commandBuffers;
    static VkQueue m_graphicsQueue, m_presentQueue;

    static std::vector<VkSemaphore> m_imageAvailableSemaphores, m_renderFinishedSemaphores;
    static std::vector<VkFence> m_inFlightFences, m_inFlightImages;
    static size_t m_currentFrame; 

    static bool m_framebufferResized;

    static VkBuffer m_vertexBuffer;
    static VkDeviceMemory m_vertexBufferMemory;

    static std::vector<char> readFile(const std::string& fileName)
    {
        std::ifstream file(fileName, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        return buffer;
    }
};
