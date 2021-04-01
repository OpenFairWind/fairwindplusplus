cmake_minimum_required(VERSION 3.16)
project(FairWind)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets WebEngineWidgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::WebEngineWidgets)

add_executable(${PROJECT_NAME} main.cpp resources.qrc ui/MainWindow.ui ui/MainWindow.cpp ui/MainWindow.hpp App.cpp App.hpp ui/WebView.cpp ui/WebView.hpp ui/WebPage.cpp ui/WebPage.hpp ui/WebPopupWindow.cpp ui/WebPopupWindow.hpp apps/IApp.cpp include/IApp.hpp apps/dashboard/Dashboard.cpp apps/dashboard/Dashboard.hpp apps/web/Web.cpp apps/web/Web.hpp apps/native/Native.cpp apps/native/Native.hpp)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()
# -DCMAKE_PREFIX_PATH="/usr/local/Cellar/qt@5/5.15.2/lib/cmake"
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
