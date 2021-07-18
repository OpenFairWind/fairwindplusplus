
set(RADAR_RESOURCE resources.qrc)
qt5_add_resources(RADAR_RESOURCE_ADDED ${RADAR_RESOURCE})

add_library(Radar SHARED
        Radar.cpp
        Radar.hpp
        ${RADAR_RESOURCE_ADDED}
        )

add_dependencies(Radar FairWindSdk)
target_link_libraries(Radar PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(Radar PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Radar
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Radar>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Radar>
)
