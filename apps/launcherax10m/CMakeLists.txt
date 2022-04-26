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

set(LAUNCHERAX10M_RESOURCE resourcesLauncherAx10m.qrc)
qt5_add_resources(LAUNCHERAX10M_RESOURCE_ADDED ${LAUNCHERAX10M_RESOURCE})

add_library(LauncherAx10m SHARED
        LauncherAx10m.cpp
        LauncherAx10m.hpp
        MainPage.cpp MainPage.hpp MainPage.ui
        ${LAUNCHERAX10M_RESOURCE_ADDED}
        )

add_dependencies(LauncherAx10m FairWindSdk)
target_link_libraries(LauncherAx10m PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Positioning ${LIBFAIRWINDSDK})
target_compile_options(LauncherAx10m PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET LauncherAx10m
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:LauncherAx10m>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:LauncherAx10m>
)
