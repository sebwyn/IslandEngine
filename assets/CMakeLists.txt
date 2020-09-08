add_subdirectory(shaders)

foreach(compiled_shader ${compiled_shaders})
    file(RELATIVE_PATH rel_compiled_shader ${CMAKE_CURRENT_SOURCE_DIR} ${compiled_shader})
    list(APPEND rel_compiled_shaders ${rel_compiled_shader})
endforeach()

set(PROJECT_ASSET_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)
#move the assets into the PROJECT_ASSET_DIR 

#TODO: add some art files
#file(GLOB_RECURSE art RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}) 

set(assets ${rel_compiled_shaders} ${art})
foreach(asset ${assets})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${asset} ${CMAKE_CURRENT_BINARY_DIR}/${asset} COPYONLY)
endforeach()
