add_executable(IslandEngine 
    main.cpp 
    Socket.cpp 
    platform/window/Window.cpp 
    platform/vulkan/Renderer.cpp
)

configure_file(platform/vulkan/Renderer.cpp.in ${PROJECT_SOURCE_DIR}/src/platform/vulkan/Renderer.cpp)

find_package(Vulkan REQUIRED)

set(libs glfw ${Vulkan_LIBRARIES} glm EnTT stb)

if(WIN32)
    set(libs ${libs} wsock32)
endif()

target_link_libraries(IslandEngine ${libs})
target_include_directories(IslandEngine PRIVATE ${Vulkan_INCLUDE_DIR})
