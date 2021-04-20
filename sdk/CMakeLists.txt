

find_package(Qt5 REQUIRED COMPONENTS
        Core
        Gui
        Network
        Widgets
        WebEngineWidgets
        )

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

add_library(fairwindsdk SHARED
        include/FairWindSdk/FairWindSDK.hpp
        include/FairWindSdk/IFairWindApp.hpp
        include/FairWindSdk/FairWindAppBase.hpp
        include/FairWindSdk/SignalKDocument.hpp
        include/FairWindSdk/FairWind.hpp
        include/FairWindSdk/App.hpp
        src/FairWind.cpp
        src/App.cpp
        src/FairWindAppBase.cpp
        src/SignalKDocument.cpp
        )

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

add_dependencies(fairwindsdk QcGaugeWidget)
add_dependencies(fairwindsdk QGeoView)
target_link_libraries(fairwindsdk
        PRIVATE
        Qt5::Core
        Qt5::Network
        Qt5::Gui
        Qt5::Widgets
        Qt5::WebEngineWidgets
        ${LIBQCGAUGEWIDGET} ${LIBQGEOVIEW}
        )

add_library(FairWindSdk ALIAS fairwindsdk)

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