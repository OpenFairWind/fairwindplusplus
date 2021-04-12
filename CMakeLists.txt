cmake_minimum_required(VERSION 3.16)
project(FairWind)
#set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()
# -DCMAKE_PREFIX_PATH="/usr/local/Cellar/qt@5/5.15.2/lib/cmake"

# Include the support to external projects
include(ExternalProject)

# Set the external install location
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

# Add to the includes
include_directories(SYSTEM ${EXTERNAL_INSTALL_LOCATION}/include)

# Add to the libraries
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Network WebEngineWidgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::WebEngineWidgets)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_subdirectory(apps/chart)
add_subdirectory(apps/dashboard)
add_subdirectory(apps/native)
add_subdirectory(apps/web)

add_executable(${PROJECT_NAME}
        main.cpp resources.qrc
        ui/MainWindow.ui ui/MainWindow.cpp ui/MainWindow.hpp
        core/App.cpp core/App.hpp
        include/IFairWindApp.hpp
        core/FairWind.cpp core/FairWind.hpp
        FairWindAppBase.cpp include/FairWindAppBase.hpp
        ui/BottomBarIcon.cpp ui/BottomBarIcon.hpp
        ui/TopBar.cpp ui/TopBar.hpp
        ui/BottomBar.cpp ui/BottomBar.hpp)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/fairwind.json
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/fairwind.json
)



