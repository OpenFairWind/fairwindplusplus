find_package(Qt5 REQUIRED COMPONENTS
        Core
        Gui
        Network
        Widgets
        WebSockets
        )

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



ExternalProject_Add(QtJsonSchema
        GIT_REPOSITORY https://github.com/OpenFairWind/QtJsonSchema.git
        CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
        TIMEOUT 360
        )
set(LIBQTJSONSCHEMA ${EXTERNAL_INSTALL_LOCATION}/lib/libqtjsonschema.so)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIBQTJSONSCHEMA ${EXTERNAL_INSTALL_LOCATION}/lib/static/qtjsonschema.lib)
    add_custom_command(
            TARGET QtJsonSchema
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${EXTERNAL_INSTALL_LOCATION}/bin/qtjsonschema.dll
            ${CMAKE_BINARY_DIR}
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(LIBQTJSONSCHEMA ${EXTERNAL_INSTALL_LOCATION}/lib/libqtjsonschema.dylib)
endif()
set(LIBQTJSONSCHEMA ${LIBQTJSONSCHEMA} PARENT_SCOPE)


ExternalProject_Add(QcGaugeWidget
        GIT_REPOSITORY https://github.com/OpenFairWind/Qt-custom-gauge-widget.git
        CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
        TIMEOUT 360
        )

set(LIBQCGAUGEWIDGET ${EXTERNAL_INSTALL_LOCATION}/lib/libqcgaugewidget.so)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIBQCGAUGEWIDGET ${EXTERNAL_INSTALL_LOCATION}/lib/static/qcgaugewidget.lib)
    add_custom_command(
            TARGET QcGaugeWidget
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${EXTERNAL_INSTALL_LOCATION}/bin/qcgaugewidget.dll
            ${CMAKE_BINARY_DIR}
    )
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
    set(LIBQGEOVIEW ${EXTERNAL_INSTALL_LOCATION}/lib/static/qgeoview.lib)
    add_custom_command(
            TARGET QGeoView
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${EXTERNAL_INSTALL_LOCATION}/bin/qgeoview.dll
            ${CMAKE_BINARY_DIR}
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(LIBQGEOVIEW ${EXTERNAL_INSTALL_LOCATION}/lib/libqgeoview.dylib)
endif()
set(LIBQGEOVIEW ${LIBQGEOVIEW} PARENT_SCOPE)

set(FAIRWINDSDK_RESOURCE resourcesSDK.qrc)
qt5_add_resources(FAIRWINDSDK_RESOURCE_ADDED ${FAIRWINDSDK_RESOURCE})

add_library(fairwindsdk SHARED
        include/FairWindSdk/FairWindSDK.hpp
        include/FairWindSdk/IApp.hpp
        include/FairWindSdk/ILayer.hpp
        include/FairWindSdk/IDisplay.hpp
        include/FairWindSdk/IConnection.hpp
        include/FairWindSdk/ILayout.hpp
        include/FairWindSdk/ISettingsTab.hpp
        include/FairWindSdk/AppBase.hpp
        include/FairWindSdk/SignalKDocument.hpp
        include/FairWindSdk/FairWind.hpp
        include/FairWindSdk/App.hpp
        include/FairWindSdk/displays/DisplayBase.hpp
        include/FairWindSdk/displays/DisplaySingleText.hpp
        include/FairWindSdk/displays/DisplayDoubleText.hpp
        include/FairWindSdk/displays/DisplayGauge.hpp
        include/FairWindSdk/displays/DisplayVerticalBarGauge.hpp
        include/FairWindSdk/displays/DisplaySimpleSwitch.hpp
        include/FairWindSdk/displays/DisplayWindAngleGauge.hpp
        include/FairWindSdk/displays/DisplayChart.hpp
        include/FairWindSdk/layers/ItemVessel.hpp
        include/FairWindSdk/layers/ItemAton.hpp
        include/FairWindSdk/layers/ItemShoreBasestations.hpp
        include/FairWindSdk/layers/ItemSignalK.hpp
        include/FairWindSdk/layers/ItemDefault.hpp
        include/FairWindSdk/layers/SignalKLayer.hpp
        include/FairWindSdk/layers/OSMLayer.hpp
        include/FairWindSdk/layers/TiledLayer.hpp
        include/FairWindSdk/layouts/LayoutBase.hpp
        include/FairWindSdk/layouts/VHGLayout.hpp
        include/FairWindSdk/layouts/GridLayout.hpp
        include/FairWindSdk/util/Units.hpp
        include/FairWindSdk/util/ExtendedJsonSchema.hpp
        include/FairWindSdk/connections/SignalKAPIClient.hpp
        include/FairWindSdk/connections/SignalKWSClient.hpp
        include/FairWindSdk/ISettings.hpp
        include/FairWindSdk/settings/FairComboBox.hpp
        include/FairWindSdk/settings/FairLineEdit.hpp
        include/FairWindSdk/settings/FairCheckBox.hpp
        include/FairWindSdk/settings/DisplaysBrowser.hpp
        include/FairWindSdk/settings/LayersBrowser.hpp

        src/FairWind.cpp
        src/App.cpp
        src/AppBase.cpp
        src/SignalKDocument.cpp
        src/displays/base/DisplayBase.cpp
        src/displays/base/singletext/DisplaySingleText.cpp
        src/displays/base/doubletext/DisplayDoubleText.cpp
        src/displays/base/gauge/DisplayGauge.cpp
        src/displays/base/gauge/DisplayVerticalBarGauge.cpp
        src/displays/base/switch/DisplaySimpleSwitch.cpp
        src/displays/wind/DisplayWindAngleGauge.cpp
        src/displays/chart/DisplayChart.cpp
        src/layers/ItemDefault.cpp
        src/layers/ItemVessel.cpp
        src/layers/ItemAton.cpp
        src/layers/ItemShoreBasestations.cpp
        src/layers/ItemSignalK.cpp
        src/layers/SignalKLayer.cpp
        src/layers/OSMLayer.cpp
        src/layers/TiledLayer.cpp
        src/layouts/LayoutBase.cpp
        src/layouts/VHGLayout.cpp
        src/layouts/GridLayout.cpp
        src/util/Units.cpp
        src/util/ExtendedJsonSchema.cpp
        src/connections/SignalKAPIClient.cpp
        src/connections/SignalKWSClient.cpp
        src/settings/FairComboBox.cpp
        src/settings/FairLineEdit.cpp
        src/settings/FairCheckBox.cpp
        src/settings/DisplaysBrowser.cpp
        src/settings/LayersBrowser.cpp)

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
add_dependencies(fairwindsdk QtJsonSchema)
add_dependencies(fairwindsdk QcGaugeWidget)
add_dependencies(fairwindsdk QGeoView)

target_link_libraries(fairwindsdk
        PRIVATE
        Qt5::Core
        Qt5::Network
        Qt5::Gui
        Qt5::Widgets
        Qt5::WebSockets
        #${LIBMARNAV}
        ${LIBQTJSONSCHEMA} ${LIBQCGAUGEWIDGET} ${LIBQGEOVIEW}
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
    set(LIBFAIRWINDSDK ${CMAKE_BINARY_DIR}/sdk/fairwindsdk.lib)
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

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_custom_command(
            TARGET fairwindsdk
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:fairwindsdk>
            ${CMAKE_BINARY_DIR}
    )
endif()

