add_subdirectory(shaders)

set(PROJECT_ASSET_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)
#move the assets into the PROJECT_ASSET_DIR 

#TODO: add some art files
#file(GLOB_RECURSE assets RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}) 

foreach(asset ${assets})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${asset} ${CMAKE_CURRENT_BINARY_DIR}/${asset} COPYONLY)
endforeach()
