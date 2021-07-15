
set(ENTERTAINMENT_RESOURCE resources.qrc)
qt5_add_resources(ENTERTAINMENT_RESOURCE_ADDED ${ENTERTAINMENT_RESOURCE})

add_library(Entertainment SHARED
        Entertainment.cpp
        Entertainment.hpp
        ${ENTERTAINMENT_RESOURCE_ADDED}
        )

add_dependencies(Entertainment FairWindSdk)
target_link_libraries(Entertainment PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(Entertainment PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Entertainment
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Entertainment>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Entertainment>
)