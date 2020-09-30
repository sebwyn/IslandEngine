#add all the external libs
option(BUILD_TESTING "" OFF)
add_subdirectory(entt)
add_subdirectory(glm)
#may need to configure this more for vulkan
#option(GLFW_BUILD_TESTS "" ON) 
add_subdirectory(glfw)

#add the stb file that we want to includes
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE stb)

#add the tinyobjloader file that we want to includes
add_library(tinyobjloader INTERFACE)
target_include_directories(tinyobjloader INTERFACE tinyobjloader)
