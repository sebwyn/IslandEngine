add_executable(IslandEngine main.cpp Socket.cpp)

find_package(Vulkan REQUIRED)

set(libs glfw ${Vulkan_LIBRARIES} glm EnTT)

if(WIN32)
    set(libs ${libs} wsock32)
endif()

target_link_libraries(IslandEngine ${libs})
target_include_directories(IslandEngine PRIVATE ${Vulkan_INCLUDE_DIR})
