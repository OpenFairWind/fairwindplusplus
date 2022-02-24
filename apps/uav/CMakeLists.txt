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

set(UAV_RESOURCE resourcesUAV.qrc)
qt5_add_resources(UAV_RESOURCE_ADDED ${UAV_RESOURCE})

add_library(UAV SHARED
        UAV.cpp
        UAV.hpp
        ${UAV_RESOURCE_ADDED}
        MainPage.cpp MainPage.hpp MainPage.ui)

add_dependencies(UAV FairWindSdk)
target_link_libraries(UAV PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Positioning  ${LIBFAIRWINDSDK})
target_compile_options(UAV PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET UAV
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:UAV>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:UAV>
)
