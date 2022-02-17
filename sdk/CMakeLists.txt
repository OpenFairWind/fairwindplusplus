set(QT_VERSION 5)

find_package(Qt${QT_VERSION} REQUIRED COMPONENTS
        Core
        Gui
        Network
        Widgets
        WebSockets
        Positioning
        )


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

ExternalProject_Add(QcSwitchWidget
        GIT_REPOSITORY https://github.com/zSelimReborn/Qt-custom-switch-widget.git
        CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
        TIMEOUT 360
        )

set(LIBQCSWITCHWIDGET ${EXTERNAL_INSTALL_LOCATION}/lib/libqcswitchwidget.so)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIBQCSWITCHWIDGET ${EXTERNAL_INSTALL_LOCATION}/lib/static/qcswitchwidget.lib)
    add_custom_command(
            TARGET QcSwitchWidget
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${EXTERNAL_INSTALL_LOCATION}/bin/qcswitchwidget.dll
            ${CMAKE_BINARY_DIR}
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(LIBQCSWITCHWIDGET ${EXTERNAL_INSTALL_LOCATION}/lib/libqcswitchwidget.dylib)
endif()
set(LIBQCSWITCHWIDGET ${LIBQCSWITCHWIDGET} PARENT_SCOPE)

ExternalProject_Add(QGeoView
        GIT_REPOSITORY https://github.com/zSelimReborn/QGeoView
        CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -DEXTERNAL_INSTALL_LOCATION=${EXTERNAL_INSTALL_LOCATION}
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
        ${FAIRWINDSDK_RESOURCE_ADDED}
        include/FairWindSdk/FairWindSDK.hpp
        include/FairWindSdk/IFairWindApp.hpp
        include/FairWindSdk/IFairWindLauncher.hpp
        include/FairWindSdk/ILayer.hpp
        include/FairWindSdk/IDisplay.hpp
        include/FairWindSdk/IConnection.hpp
        include/FairWindSdk/ILayout.hpp
        include/FairWindSdk/ISettingsTab.hpp
        include/FairWindSdk/FairWindApp.hpp
        include/FairWindSdk/PageBase.hpp
        include/FairWindSdk/PanelBase.hpp
        include/FairWindSdk/SignalKDocument.hpp
        include/FairWindSdk/FairWind.hpp
        include/FairWindSdk/AppItem.hpp
        include/FairWindSdk/displays/DisplayBase.hpp
        include/FairWindSdk/displays/DisplaySingleText.hpp
        include/FairWindSdk/displays/DisplayDoubleText.hpp
        include/FairWindSdk/displays/DisplayGauge.hpp
        include/FairWindSdk/displays/DisplayBarGauge.hpp
        include/FairWindSdk/displays/DisplaySimpleSwitch.hpp
        include/FairWindSdk/displays/DisplayToggleSwitch.hpp
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
        include/FairWindSdk/layers/GeoJsonLayer.hpp
        include/FairWindSdk/layers/ESRILayer.hpp
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

        src/ui/Warning.cpp include/FairWindSdk/ui/Warning.hpp src/ui/Warning.ui
        src/ui/Colophon.cpp include/FairWindSdk/ui/Colophon.hpp src/ui/Colophon.ui

        src/FairWind.cpp
        src/AppItem.cpp
        src/FairWindApp.cpp
        src/PageBase.cpp
        src/SignalKDocument.cpp
        src/displays/base/DisplayBase.cpp
        src/displays/base/singletext/DisplaySingleText.cpp
        src/displays/base/doubletext/DisplayDoubleText.cpp
        src/displays/base/gauge/DisplayGauge.cpp
        src/displays/base/gauge/DisplayBarGauge.cpp
        src/displays/base/switch/DisplaySimpleSwitch.cpp
        src/displays/base/switch/DisplayToggleSwitch.cpp
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
        src/layers/GeoJsonLayer.cpp
        src/layers/ESRILayer.cpp
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
        src/settings/LayersBrowser.cpp
        src/PanelBase.cpp

        ${FAIRWINDSDK_RESOURCE_ADDED}
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

add_dependencies(fairwindsdk QtJsonSchema)
add_dependencies(fairwindsdk QcGaugeWidget)
add_dependencies(fairwindsdk QcSwitchWidget)
add_dependencies(fairwindsdk QGeoView)

target_link_libraries(fairwindsdk
        PRIVATE
        Qt${QT_VERSION}::Core
        Qt${QT_VERSION}::Network
        Qt${QT_VERSION}::Gui
        Qt${QT_VERSION}::Widgets
        Qt${QT_VERSION}::WebSockets
        ${LIBQTJSONSCHEMA} ${LIBQCGAUGEWIDGET} ${LIBQCSWITCHWIDGET} ${LIBQGEOVIEW}
        )

add_library(FairWindSdk ALIAS fairwindsdk)

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

