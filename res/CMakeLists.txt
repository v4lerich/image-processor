project(image-processor-resources)

add_custom_target(${PROJECT_NAME} ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Rubik_font/ ${RESOURCE_PATH}/fonts/Rubikfont/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ ${RESOURCE_PATH}/shaders/)
