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
        Sql
        )

find_package (SQLite3)

include_directories(${SQLite3_INCLUDE_DIRS})

set(PORTOLANO_RESOURCE resourcesPortolano.qrc)
qt5_add_resources(PORTOLANO_RESOURCE_ADDED ${PORTOLANO_RESOURCE})

add_library(Portolano SHARED
        Portolano.cpp
        Portolano.hpp
        ${PORTOLANO_RESOURCE_ADDED}
        MainPage.cpp MainPage.hpp MainPage.ui ResultItem.cpp ResultItem.hpp ResultItem.ui)

add_dependencies(Portolano FairWindSdk)
target_link_libraries(Portolano PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Sql Qt${QT_VERSION}::Positioning ${LIBFAIRWINDSDK} ${SQLite3_LIBRARIES})
target_compile_options(Portolano PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Portolano
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Portolano>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Portolano>
)
