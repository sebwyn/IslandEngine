#add all the external libs
option(BUILD_TESTING "" OFF)
add_subdirectory(entt)
add_subdirectory(glm)
#may need to configure this more for vulkan
option(GLFW_BUILD_TESTS "" ON) 
add_subdirectory(glfw)
