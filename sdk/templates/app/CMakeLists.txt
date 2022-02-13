
set(__APPNAME___RESOURCE resources__Appname__.qrc)
qt5_add_resources(__APPNAME___RESOURCE_ADDED ${__APPNAME___RESOURCE})

add_library(__Appname__ SHARED
        __Appname__.cpp
        __Appname__.hpp
        MainPage.cpp MainPage.hpp MainPage.ui
        ${__APPNAME___RESOURCE_ADDED}
        )

add_dependencies(__Appname__ FairWindSdk)
target_link_libraries(__Appname__ PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(__Appname__ PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET __Appname__
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:__Appname__>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:__Appname__>
)
