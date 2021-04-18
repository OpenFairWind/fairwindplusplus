include_directories(SYSTEM ../../include)

ExternalProject_Add(QGeoView
        GIT_REPOSITORY https://github.com/OpenFairWind/QGeoView.git
        CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
        TIMEOUT 360
        )
set(LIBQGEOVIEW ${EXTERNAL_INSTALL_LOCATION}/lib/libqgeoview.so)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIBQGEOVIEW ${EXTERNAL_INSTALL_LOCATION}/lib/libqgeoview.dll)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(LIBQGEOVIEW ${EXTERNAL_INSTALL_LOCATION}/lib/libqgeoview.dylib)
endif()

set(CHART_RESOURCE resources.qrc)
qt5_add_resources(CHART_RESOURCE_ADDED ${CHART_RESOURCE})

add_library(Chart SHARED
        Chart.cpp
        Chart.hpp
        ../../core/App.cpp
        ../../core/App.hpp
        ../../core/FairWind.cpp
        ../../core/FairWind.hpp
        ../../lib/src/SignalKDocument.cpp
        ../../include/SignalKDocument.hpp
        ../../lib/src/FairWindAppBase.cpp
        ../../include/FairWindAppBase.hpp
        ../../include/IFairWindApp.hpp
        ${CHART_RESOURCE_ADDED}
        )

add_dependencies(Chart QGeoView)
target_link_libraries(Chart PRIVATE Qt5::Widgets Qt5::Network ${LIBQGEOVIEW})
target_compile_options(Chart PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Chart
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Chart>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Chart>
)