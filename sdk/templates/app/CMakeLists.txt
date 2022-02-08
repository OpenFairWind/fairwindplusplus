find_package (SQLite3)

include_directories(${SQLite3_INCLUDE_DIRS})

find_package(Qt5 REQUIRED COMPONENTS Widgets Network Sql Positioning)

set(__APPNAME___RESOURCE resources__Appname__.qrc)
qt5_add_resources(__APPNAME___RESOURCE_ADDED ${__APPNAME___RESOURCE})

add_library(__Appname__ SHARED
        __Appname__.cpp
        __Appname__.hpp
        ${PORTOLANO_RESOURCE_ADDED}
        MainPage.cpp MainPage.hpp MainPage.ui
        ResultItem.cpp ResultItem.hpp ResultItem.ui
        )

add_dependencies(__Appname__ FairWindSdk)
target_link_libraries(__Appname__ PRIVATE Qt5::Widgets Qt5::Network Qt5::Sql Qt5::Positioning ${LIBFAIRWINDSDK} ${SQLite3_LIBRARIES})
target_compile_options(__Appname__ PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET __Appname__
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:__Appname__>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:__Appname__>
)
