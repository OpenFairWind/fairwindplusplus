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

set(EXTERNAL_RESOURCE resourcesExternal.qrc)
qt5_add_resources(EXTERNAL_RESOURCE_ADDED ${EXTERNAL_RESOURCE})

add_library(External SHARED
        External.cpp
        External.hpp
        ${EXTERNAL_RESOURCE_ADDED}
        )

add_dependencies(External FairWindSdk)
target_link_libraries(External PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Positioning ${LIBFAIRWINDSDK})
target_compile_options(External PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET External
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:External>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:External>
)
