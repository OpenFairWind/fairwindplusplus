
set(VIDEO_RESOURCE resources.qrc)
qt5_add_resources(VIDEO_RESOURCE_ADDED ${VIDEO_RESOURCE})

add_library(Video SHARED
        Video.cpp
        Video.hpp
        ${VIDEO_RESOURCE_ADDED}
        )

add_dependencies(Video FairWindSdk)
target_link_libraries(Video PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(Video PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Video
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Video>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Video>
)