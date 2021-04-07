cmake_minimum_required(VERSION 3.16)
project(FairWind)

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

ExternalProject_Add(QGeoView
        GIT_REPOSITORY https://github.com/OpenFairWind/QGeoView.git
        CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
        TIMEOUT 360
        )
set(LIBQGEOVIEW ${EXTERNAL_INSTALL_LOCATION}/lib/libqgeoview.a)
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(LIBQGEOVIEW ${EXTERNAL_INSTALL_LOCATION}/lib/libqgeoview.dylib)
endif()

add_library(Chart SHARED
        extensions/apps/chart/Chart.cpp extensions/apps/chart/Chart.hpp
        include/FairWindApp.hpp
        extensions/apps/FairWindApp.cpp include/FairWindApp.hpp
        extensions/FairWindExtension.cpp include/FairWindExtension.hpp
        )

add_dependencies(Chart QGeoView)
target_link_libraries(Chart PRIVATE Qt5::Widgets Qt5::Network ${LIBQGEOVIEW})
target_compile_options(Chart PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Chart
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Chart>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/extensions/$<TARGET_FILE_NAME:Chart>
)

add_library(Dashboard SHARED
        extensions/apps/dashboard/Dashboard.cpp extensions/apps/dashboard/Dashboard.hpp
        include/FairWindApp.hpp
        extensions/apps/FairWindApp.cpp include/FairWindApp.hpp
        extensions/FairWindExtension.cpp include/FairWindExtension.hpp)
target_link_libraries(Dashboard PRIVATE Qt5::Widgets)
target_compile_options(Dashboard PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Dashboard
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Dashboard>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/extensions/$<TARGET_FILE_NAME:Dashboard>
)


add_library(Web SHARED
        extensions/plugins/web/Web.cpp extensions/plugins/web/Web.hpp
        include/FairWindPlugin.hpp
        extensions/plugins/FairWindPlugin.cpp include/FairWindPlugin.hpp
        extensions/FairWindExtension.cpp include/FairWindExtension.hpp
        extensions/plugins/web/WebView.cpp extensions/plugins/web/WebView.hpp
        extensions/plugins/web/WebPage.cpp extensions/plugins/web/WebPage.hpp
        extensions/plugins/web/WebPopupWindow.cpp extensions/plugins/web/WebPopupWindow.hpp)
target_link_libraries(Web PRIVATE Qt5::Widgets Qt5::WebEngineWidgets)
target_compile_options(Web PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Web
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Web>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/extensions/$<TARGET_FILE_NAME:Web>
)

add_library(Native SHARED
        extensions/plugins/native/Native.cpp extensions/plugins/native/Native.hpp
        include/FairWindPlugin.hpp
        extensions/plugins/FairWindPlugin.cpp include/FairWindPlugin.hpp
        extensions/FairWindExtension.cpp include/FairWindExtension.hpp)
target_link_libraries(Native PRIVATE Qt5::Widgets)
target_compile_options(Native PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Native
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Native>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/extensions/$<TARGET_FILE_NAME:Native>
)

add_executable(${PROJECT_NAME}
        main.cpp resources.qrc
        ui/MainWindow.ui ui/MainWindow.cpp ui/MainWindow.hpp
        core/App.cpp core/App.hpp
        include/IFairWindApp.hpp
        include/IFairWindPlugin.hpp
        include/FairWindExtension.hpp
        include/FairWindApp.hpp
        include/FairWindPlugin.hpp
        core/FairWind.cpp core/FairWind.hpp
        extensions/FairWindExtension.cpp
        extensions/plugins/FairWindPlugin.cpp
        extensions/apps/FairWindApp.cpp)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/fairwind.json
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/fairwind.json
)



