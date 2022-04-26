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

set(RADAR_RESOURCE resourcesRadar.qrc)
qt5_add_resources(RADAR_RESOURCE_ADDED ${RADAR_RESOURCE})

add_library(Radar SHARED
        Radar.cpp
        Radar.hpp
        ${RADAR_RESOURCE_ADDED}
        MainPage.cpp MainPage.hpp MainPage.ui)

add_dependencies(Radar FairWindSdk)
target_link_libraries(Radar PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Positioning ${LIBFAIRWINDSDK})
target_compile_options(Radar PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Radar
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Radar>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Radar>
)
