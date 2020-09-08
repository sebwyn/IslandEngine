#build the shaders here
file(GLOB_RECURSE KERNELS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.vert *.frag)
#requires glslc to be in path

foreach(KERNEL ${KERNELS})
    set(K ${CMAKE_CURRENT_SOURCE_DIR}/${KERNEL})
    set(COMPILED_KERNEL ${CMAKE_CURRENT_BINARY_DIR}/${KERNEL}.spv)
    add_custom_command(OUTPUT ${COMPILED_KERNEL}
        COMMAND glslc ${K} -g -o ${COMPILED_KERNEL}
        DEPENDS ${K}
        COMMENT "Rebuilding ${COMPILED_KERNEL}" )
    message(STATUS "Generating build commands for ${COMPILED_KERNEL}")
    list(APPEND COMPILED_KERNELS ${COMPILED_KERNEL})
endforeach()

add_custom_target(shaders ALL DEPENDS ${KERNELS} ${COMPILED_KERNELS})
