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

/* TODO: actually make texture and buffer classes 
 * TODO: think about how to organize all of the init vulkan code
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
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    struct Vertex {
        glm::vec2 pos;
        glm::vec3 color;
        glm::vec2 texCoord;

        static VkVertexInputBindingDescription getBindindDescription()
        {
            VkVertexInputBindingDescription bindingDescription;
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }
    };

    static std::vector<Vertex> m_vertices;
    static std::vector<uint16_t> m_indices;

    //Lots of vulkan shit I barely understand
    static std::string m_texturePath;
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

    static void updateUniformBuffers(uint32_t currentImage);

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
    static void createDescriptorSetLayout();
    static void createGraphicsPipeline();
    static void createFramebuffers();
    static void createCommandPool();

    static void createTextureImage();
    static void createTextureImageView();
    static void createTextureSampler();

    static void createVertexBuffer();
    static void createIndexBuffer();

    static void createUniformBuffers();
    static void createDescriptorPool();
    static void createDescriptorSets();

    static void createCommandBuffers();
    static void createSyncObjects();


    //TODO: make this asynchronous
    static VkCommandBuffer beginSingleTimeCommands(); 
    static void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    static void createImage(uint32_t width, uint32_t height, VkFormat format, 
        VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags 
        properties, VkImage& image, VkDeviceMemory& imageMemory);
    static VkImageView createImageView(VkImage image, VkFormat format);

    static void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

    static void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& memory);
    static void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    static void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

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
    static VkDescriptorSetLayout m_descriptorSetLayout;
    static VkPipelineLayout m_pipelineLayout;
    static VkPipeline m_graphicsPipeline;

    static VkCommandPool m_commandPool;
    static std::vector<VkCommandBuffer> m_commandBuffers;
    static VkQueue m_graphicsQueue, m_presentQueue;

    static std::vector<VkSemaphore> m_imageAvailableSemaphores, m_renderFinishedSemaphores;
    static std::vector<VkFence> m_inFlightFences, m_inFlightImages;
    static size_t m_currentFrame; 

    static bool m_framebufferResized;

    static VkImage m_textureImage;
    static VkDeviceMemory m_textureImageMemory;
    static VkImageView m_textureImageView;
    static VkSampler m_textureSampler;

    static VkBuffer m_vertexBuffer;
    static VkDeviceMemory m_vertexBufferMemory;
    static VkBuffer m_indexBuffer;
    static VkDeviceMemory m_indexBufferMemory;

    static std::vector<VkBuffer> m_uniformBuffers;
    static std::vector<VkDeviceMemory> m_uniformBuffersMemory;

    static VkDescriptorPool m_descriptorPool; 
    static std::vector<VkDescriptorSet> m_descriptorSets;

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
