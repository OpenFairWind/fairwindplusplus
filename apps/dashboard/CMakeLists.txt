set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(SYSTEM ../../include)

set(DASHBOARD_RESOURCE resources.qrc)
qt5_add_resources(DASHBOARD_RESOURCE_ADDED ${DASHBOARD_RESOURCE})

add_library(Dashboard SHARED
        Dashboard.cpp
        Dashboard.hpp
        ../../FairWindAppBase.cpp
        ../../include/FairWindAppBase.hpp
        ${PROJECT_SOURCE_DIR}/include/IFairWindApp.hpp
        ${DASHBOARD_RESOURCE_ADDED}
        )
target_link_libraries(Dashboard PRIVATE Qt5::Widgets)
target_compile_options(Dashboard PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Dashboard
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Dashboard>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Dashboard>
)