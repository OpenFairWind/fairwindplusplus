
set(SONAR_RESOURCE resourcesSonar.qrc)
qt5_add_resources(SONAR_RESOURCE_ADDED ${SONAR_RESOURCE})

add_library(Sonar SHARED
        Sonar.cpp
        Sonar.hpp
        ${SONAR_RESOURCE_ADDED}
        )

add_dependencies(Sonar FairWindSdk)
target_link_libraries(Sonar PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(Sonar PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Sonar
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Sonar>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Sonar>
)
