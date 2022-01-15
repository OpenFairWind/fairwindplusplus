
set(PORTOLANO_RESOURCE resourcesPortolano.qrc)
qt5_add_resources(PORTOLANO_RESOURCE_ADDED ${PORTOLANO_RESOURCE})

add_library(Portolano SHARED
        Portolano.cpp
        Portolano.hpp
        ${PORTOLANO_RESOURCE_ADDED}
        MainPage.cpp MainPage.hpp MainPage.ui)

add_dependencies(Portolano FairWindSdk)
target_link_libraries(Portolano PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(Portolano PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Portolano
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Portolano>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Portolano>
)
