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

set(DASHBOARD_RESOURCE resourcesDashboard.qrc)
qt5_add_resources(DASHBOARD_RESOURCE_ADDED ${DASHBOARD_RESOURCE})

add_library(Dashboard SHARED
        Dashboard.cpp
        Dashboard.hpp
        MainPage.cpp
        MainPage.hpp
        MainPage.ui
        ${DASHBOARD_RESOURCE_ADDED}
        )

add_dependencies(Dashboard FairWindSdk)
target_link_libraries(Dashboard PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Positioning ${LIBFAIRWINDSDK})
target_compile_options(Dashboard PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Dashboard
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Dashboard>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Dashboard>
)
