include_directories(SYSTEM ../../include)

set(NATIVE_RESOURCE resources.qrc)
qt5_add_resources(NATIVE_RESOURCE_ADDED ${NATIVE_RESOURCE})

add_library(Native SHARED
        Native.cpp
        Native.hpp
        ../../FairWindAppBase.cpp
        ../../include/FairWindAppBase.hpp
        ${NATIVE_RESOURCE_ADDED}
        )
target_link_libraries(Native PRIVATE Qt5::Widgets)
target_compile_options(Native PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Native
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Native>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Native>
)