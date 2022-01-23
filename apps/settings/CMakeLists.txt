
set(SETTINGS_RESOURCE resourcesSettings.qrc)
qt5_add_resources(SETTINGS_RESOURCE_ADDED ${SETTINGS_RESOURCE})

add_library(Settings SHARED
        Settings.cpp
        Settings.hpp
        MainPage.cpp MainPage.hpp MainPage.ui

        browser/Browser.cpp browser/Browser.hpp browser/Browser.ui
        browser/Browser.cpp browser/Browser.hpp browser/Browser.ui
        browser/UIArray.cpp browser/UIArray.hpp browser/UIArray.ui
        browser/UIItem.cpp browser/UIItem.hpp browser/UIItem.ui
        browser/UIObject.cpp browser/UIObject.hpp browser/UIObject.ui
        browser/UIValue.cpp browser/UIValue.hpp browser/UIValue.ui
        general/General.cpp general/General.hpp general/General.ui
        extensions/Extensions.cpp extensions/Extensions.hpp extensions/Extensions.ui
        ${SETTINGS_RESOURCE_ADDED}
        extensions/ExtensionItem.cpp extensions/ExtensionItem.hpp extensions/ExtensionItem.ui)

add_dependencies(Settings FairWindSdk)
target_link_libraries(Settings PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(Settings PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Settings
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Settings>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Settings>
)
