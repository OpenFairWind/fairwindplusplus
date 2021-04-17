include_directories(SYSTEM ../../include)

set(WEB_RESOURCE resources.qrc)
qt5_add_resources(WEB_RESOURCE_ADDED ${WEB_RESOURCE})

add_library(Web SHARED
        Web.cpp
        Web.hpp
        ../../lib/src/FairWindAppBase.cpp
        ../../include/FairWindAppBase.hpp
        WebView.cpp WebView.hpp
        WebPage.cpp WebPage.hpp
        WebPopupWindow.cpp WebPopupWindow.hpp
        ${WEB_RESOURCE_ADDED}
        )
target_link_libraries(Web PRIVATE Qt5::Widgets Qt5::WebEngineWidgets)
target_compile_options(Web PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Web
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Web>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Web>
)
