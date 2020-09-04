add_executable(IslandEngine main.cpp)

find_package(Vulkan REQUIRED)

target_link_libraries(IslandEngine glfw ${Vulkan_LIBRARIES} glm EnTT)
target_include_directories(IslandEngine PRIVATE ${Vulkan_INCLUDE_DIR})
