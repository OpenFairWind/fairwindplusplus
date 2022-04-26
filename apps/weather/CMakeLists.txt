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

set(WEATHER_RESOURCE resourcesWeather.qrc)
qt5_add_resources(WEATHER_RESOURCE_ADDED ${WEATHER_RESOURCE})

add_library(Weather SHARED
        Weather.cpp
        Weather.hpp
        ${WEATHER_RESOURCE_ADDED}
        MainPage.cpp MainPage.hpp MainPage.ui)

add_dependencies(Weather FairWindSdk)
target_link_libraries(Weather PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Positioning ${LIBFAIRWINDSDK})
target_compile_options(Weather PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Weather
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Weather>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Weather>
)
