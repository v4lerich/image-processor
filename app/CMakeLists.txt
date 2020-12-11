project(image-processor)

add_executable(${PROJECT_NAME}
        main.cc)

install(TARGETS ${PROJECT_NAME}
        DESTINATION bin)