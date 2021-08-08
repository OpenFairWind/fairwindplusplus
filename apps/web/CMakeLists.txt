

set(WEB_RESOURCE resourcesWeb.qrc)
qt5_add_resources(WEB_RESOURCE_ADDED ${WEB_RESOURCE})

add_library(Web SHARED
        Web.cpp
        Web.hpp
        WebView.cpp WebView.hpp
        WebPage.cpp WebPage.hpp
        WebPopupWindow.cpp WebPopupWindow.hpp
        ${WEB_RESOURCE_ADDED}
        )

add_dependencies(Web FairWindSdk)
target_link_libraries(Web PRIVATE Qt5::Widgets Qt5::WebEngineWidgets ${LIBFAIRWINDSDK})
target_compile_options(Web PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Web
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Web>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Web>
)
