
set(CHANDLERY_RESOURCE resourcesChandlery.qrc)
qt5_add_resources(CHANDLERY_RESOURCE_ADDED ${CHANDLERY_RESOURCE})

add_library(Chandlery SHARED
        Chandlery.cpp
        Chandlery.hpp
        ${CHANDLERY_RESOURCE_ADDED}
        MainPage.cpp MainPage.hpp MainPage.ui)

add_dependencies(Chandlery FairWindSdk)
target_link_libraries(Chandlery PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(Chandlery PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Chandlery
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Chandlery>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Chandlery>
)
