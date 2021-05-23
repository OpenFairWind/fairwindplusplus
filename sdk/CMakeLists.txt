

find_package(Qt5 REQUIRED COMPONENTS
        Core
        Gui
        Network
        Widgets
        WebEngineWidgets
        )

#ExternalProject_Add(variant
#        GIT_REPOSITORY https://github.com/mpark/variant.git
#        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#        TIMEOUT 360
#        )

#ExternalProject_Add(marnav
#        GIT_REPOSITORY https://github.com/mariokonrad/marnav.git
#        CMAKE_ARGS -DENABLE_STATIC=OFF -DENABLE_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#        TIMEOUT 360
#        )
#set(LIBMARNAV ${EXTERNAL_INSTALL_LOCATION}/lib/libmarnav.so)
#if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#    set(LIBMARNAV ${EXTERNAL_INSTALL_LOCATION}/lib/libmarnav.dll)
#elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#    set(LIBMARNAV ${EXTERNAL_INSTALL_LOCATION}/lib/libmarnav.dylib)
#endif()
#set(LIBMARNAV ${LIBMARNAV} PARENT_SCOPE)

ExternalProject_Add(QcGaugeWidget
        GIT_REPOSITORY https://github.com/OpenFairWind/Qt-custom-gauge-widget.git
        CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
        TIMEOUT 360
        )
set(LIBQCGAUGEWIDGET ${EXTERNAL_INSTALL_LOCATION}/lib/libqcgaugewidget.so)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIBQCGAUGEWIDGET ${EXTERNAL_INSTALL_LOCATION}/lib/libqcgaugewidget.dll)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(LIBQCGAUGEWIDGET ${EXTERNAL_INSTALL_LOCATION}/lib/libqcgaugewidget.dylib)
endif()
set(LIBQCGAUGEWIDGET ${LIBQCGAUGEWIDGET} PARENT_SCOPE)

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
set(LIBQGEOVIEW ${LIBQGEOVIEW} PARENT_SCOPE)

set(FAIRWINDSDK_RESOURCE resources.qrc)
qt5_add_resources(FAIRWINDSDK_RESOURCE_ADDED ${FAIRWINDSDK_RESOURCE})

add_library(fairwindsdk SHARED
        include/FairWindSdk/FairWindSDK.hpp
        include/FairWindSdk/IFairWindApp.hpp
        include/FairWindSdk/IFairWindLayer.hpp
        include/FairWindSdk/FairWindAppBase.hpp
        include/FairWindSdk/SignalKDocument.hpp
        include/FairWindSdk/FairWind.hpp
        include/FairWindSdk/App.hpp
        include/FairWindSdk/DisplaySingleText.hpp
        include/FairWindSdk/DisplayDoubleText.hpp
        include/FairWindSdk/QGVItemVessel.hpp
        include/FairWindSdk/QGVItemAton.hpp
        include/FairWindSdk/QGVItemShoreBasestations.hpp
        include/FairWindSdk/QGVItemSignalK.hpp
        include/FairWindSdk/SignalKLayer.hpp
        src/FairWind.cpp
        src/App.cpp
        src/FairWindAppBase.cpp
        src/SignalKDocument.cpp
        src/display/base/singletext/DisplaySingleText.cpp
        src/display/base/doubletext/DisplayDoubleText.cpp
        src/display/position/DisplayPosition.cpp src/display/position/DisplayPosition.hpp
        src/display/chart/DisplayChart.cpp include/FairWindSdk/DisplayChart.hpp
        src/display/chart/QGVItemVessel.cpp
        src/display/chart/QGVItemAton.cpp
        src/display/chart/QGVItemShoreBasestations.cpp
        src/display/chart/QGVItemSignalK.cpp
        src/display/chart/SignalKLayer.cpp
        ${FAIRWINDSDK_RESOURCE_ADDED}
        src/display/chart/QGVItemDefault.cpp include/FairWindSdk/QGVItemDefault.hpp src/display/chart/FairWindOSMLayer.cpp include/FairWindSdk/FairWindOSMLayer.hpp src/display/chart/FairWindTiledLayer.cpp include/FairWindSdk/FairWindTiledLayer.hpp)

target_include_directories(fairwindsdk
        PUBLIC
        include
        PRIVATE
        include/FairWindSdk
        )

target_compile_definitions(fairwindsdk
        PRIVATE
        FAIRWINDSDK_EXPORT
        )

#add_dependencies(fairwindsdk variant)
#add_dependencies(fairwindsdk marnav)
add_dependencies(fairwindsdk QcGaugeWidget)
add_dependencies(fairwindsdk QGeoView)
target_link_libraries(fairwindsdk
        PRIVATE
        Qt5::Core
        Qt5::Network
        Qt5::Gui
        Qt5::Widgets
        Qt5::WebEngineWidgets
        #${LIBMARNAV}
        ${LIBQCGAUGEWIDGET} ${LIBQGEOVIEW}
        )

add_library(FairWindSdk ALIAS fairwindsdk )

#install(TARGETS fairwindsdk LIBRARY
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib/static
#        )
#
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
#        DESTINATION include
#        FILES_MATCHING PATTERN "*.h*"
#        )

set(LIBFAIRWINDSDK ${EXTERNAL_INSTALL_LOCATION}/lib/libfairwindsdk.so)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIBFAIRWINDSDK ${EXTERNAL_INSTALL_LOCATION}/lib/libfairwindsdk.dll)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(LIBFAIRWINDSDK ${EXTERNAL_INSTALL_LOCATION}/lib/libfairwindsdk.dylib)
endif()
set(LIBFAIRWINDSDK ${LIBFAIRWINDSDK} PARENT_SCOPE)

add_custom_command(
        TARGET fairwindsdk
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/include/FairWindSdk
        ${EXTERNAL_INSTALL_LOCATION}/include/FairWindSdk
)

add_custom_command(
        TARGET fairwindsdk
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:fairwindsdk>
        ${EXTERNAL_INSTALL_LOCATION}/lib/
)