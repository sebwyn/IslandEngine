#build the shaders here
file(GLOB_RECURSE KERNELS *.vert *.frag)
#message(${KERNELS})

#requires glslc to be in path

foreach(KERNEL ${KERNELS})
    add_custom_command(OUTPUT ${KERNEL}.spv
        COMMAND glslc ${KERNEL} -g -o ${KERNEL}.spv
        DEPENDS ${KERNEL}
        COMMENT "Rebuilding ${KERNEL}.spv" )
    message(STATUS "Generating build commands for ${KERNEL}.spv")
    list(APPEND COMPILED_KERNELS ${KERNEL}.spv)
endforeach()

add_custom_target(shaders ALL DEPENDS ${KERNELS} ${COMPILED_KERNELS})

set(compiled_shaders ${COMPILED_KERNELS} PARENT_SCOPE)
