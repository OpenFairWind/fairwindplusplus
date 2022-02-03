
find_package (SQLite3)

include_directories(${SQLite3_INCLUDE_DIRS})


find_package(Qt5 REQUIRED COMPONENTS Widgets Network Sql Positioning)

set(PORTOLANO_RESOURCE resourcesPortolano.qrc)
qt5_add_resources(PORTOLANO_RESOURCE_ADDED ${PORTOLANO_RESOURCE})

add_library(Portolano SHARED
        Portolano.cpp
        Portolano.hpp
        ${PORTOLANO_RESOURCE_ADDED}
        MainPage.cpp MainPage.hpp MainPage.ui ResultItem.cpp ResultItem.hpp ResultItem.ui)

add_dependencies(Portolano FairWindSdk)
target_link_libraries(Portolano PRIVATE Qt5::Widgets Qt5::Network Qt5::Sql Qt5::Positioning ${LIBFAIRWINDSDK} ${SQLite3_LIBRARIES})
target_compile_options(Portolano PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Portolano
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Portolano>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Portolano>
)
