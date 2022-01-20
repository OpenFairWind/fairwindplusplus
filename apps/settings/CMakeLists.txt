
set(SETTINGS_RESOURCE resourcesSettings.qrc)
qt5_add_resources(SETTINGS_RESOURCE_ADDED ${SETTINGS_RESOURCE})

add_library(Settings SHARED
        Settings.cpp
        Settings.hpp
        MainPage.cpp MainPage.hpp MainPage.ui
        general/General.cpp general/General.hpp general/General.ui
        browser/Browser.cpp browser/Browser.hpp browser/Browser.ui
        browser/UIArray.cpp browser/UIArray.hpp browser/UIArray.ui
        browser/UIItem.cpp browser/UIItem.hpp browser/UIItem.ui
        browser/UIObject.cpp browser/UIObject.hpp browser/UIObject.ui
        #applications/Applications.cpp applications/Applications.hpp applications/Applications.ui
        ${SETTINGS_RESOURCE_ADDED}
        general/General.cpp general/General.hpp general/General.ui browser/Browser.cpp browser/Browser.hpp browser/Browser.ui)

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
