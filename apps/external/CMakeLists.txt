set(EXTERNAL_RESOURCE resourcesExternal.qrc)
qt5_add_resources(EXTERNAL_RESOURCE_ADDED ${EXTERNAL_RESOURCE})

add_library(External SHARED
        External.cpp
        External.hpp
        ${EXTERNAL_RESOURCE_ADDED}
        )

add_dependencies(External FairWindSdk)
target_link_libraries(External PRIVATE Qt5::Widgets Qt5::Network ${LIBFAIRWINDSDK})
target_compile_options(External PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET External
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:External>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:External>
)
