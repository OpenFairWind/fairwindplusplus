set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)

find_package(Qt${QT_VERSION} REQUIRED COMPONENTS
        Core
        Gui
        Network
        Widgets
        WebSockets
        Positioning
        )

set(SONAR_RESOURCE resourcesSonar.qrc)
qt5_add_resources(SONAR_RESOURCE_ADDED ${SONAR_RESOURCE})

add_library(Sonar SHARED
        Sonar.cpp
        Sonar.hpp
        ${SONAR_RESOURCE_ADDED}
        MainPage.cpp MainPage.hpp MainPage.ui)

add_dependencies(Sonar FairWindSdk)
target_link_libraries(Sonar PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Positioning  ${LIBFAIRWINDSDK})
target_compile_options(Sonar PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Sonar
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Sonar>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Sonar>
)
