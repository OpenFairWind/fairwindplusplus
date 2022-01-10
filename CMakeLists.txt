cmake_minimum_required(VERSION 3.18)
project(FairWind)


if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()
# -DCMAKE_PREFIX_PATH="/usr/local/opt/qt5/"

# Include the support to external projects
include(ExternalProject)

# Set the external install location
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

# Add to the includes
include_directories(SYSTEM ${EXTERNAL_INSTALL_LOCATION}/include)

# Add include sdk
include_directories(SYSTEM sdk/include)

# Add to the libraries
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

#set (CMAKE_PREFIX_PATH "C:\\Qt\\5.9.9\\mingw53_32\\")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Network WebSockets Xml)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::WebSockets Qt5::Xml)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_subdirectory(sdk)

add_subdirectory(apps)

add_executable(${PROJECT_NAME}
        main.cpp resources.qrc
        ui/MainWindow.ui ui/MainWindow.cpp ui/MainWindow.hpp
        ui/colophon/Colophon.cpp ui/colophon/Colophon.hpp
        ui/topbar/TopBar.cpp ui/topbar/TopBar.hpp
        ui/bottombar/BottomBar.cpp ui/bottombar/BottomBar.hpp
        ui/apps/Apps.cpp ui/apps/Apps.hpp
        ui/settings/Settings.cpp ui/settings/Settings.hpp
        ui/settings/generic/Generic.cpp ui/settings/generic/Generic.hpp
        ui/settings/connections/Connections.cpp ui/settings/connections/Connections.hpp
        ui/settings/applications/Applications.cpp ui/settings/applications/Applications.hpp
        )

add_dependencies(${PROJECT_NAME} FairWindSdk)
target_link_libraries(${PROJECT_NAME} PRIVATE ${REQUIRED_LIBS_QUALIFIED} ${LIBFAIRWINDSDK})




if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/fairwind.json")
else()
    message("Creating default configuration file: ${CMAKE_CURRENT_SOURCE_DIR}/fairwind.json")

    add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/fairwind.json.sample
            ${CMAKE_CURRENT_SOURCE_DIR}/fairwind.json
    )
endif()



add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/fairwind.json
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/fairwind.json
)



