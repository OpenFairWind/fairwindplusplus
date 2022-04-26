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

set(IMSF_RESOURCE resourcesIMSF.qrc)
qt5_add_resources(IMSF_RESOURCE_ADDED ${IMSF_RESOURCE})

add_library(IMSF SHARED
        IMSF.cpp
        IMSF.hpp
        MainPage.cpp MainPage.hpp MainPage.ui
        Flag.cpp Flag.hpp Flag.ui
        ${IMSF_RESOURCE_ADDED}
        )

add_dependencies(IMSF FairWindSdk)
target_link_libraries(IMSF PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Positioning ${LIBFAIRWINDSDK})
target_compile_options(IMSF PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET IMSF
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:IMSF>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:IMSF>
)
