project(wave-generator-resources)

add_custom_target(${PROJECT_NAME})

add_custom_target(TARGET ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Rubik_font/ ${RESOURCE_PATH}/fonts/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders/ ${RESOURCE_PATH}/shaders/)
