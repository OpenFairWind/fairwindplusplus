
set(UAV_RESOURCE resourcesUAV.qrc)
qt5_add_resources(UAV_RESOURCE_ADDED ${UAV_RESOURCE})

add_library(UAV SHARED
        UAV.cpp
        UAV.hpp
        ${UAV_RESOURCE_ADDED}
        )

add_dependencies(UAV FairWindSdk)
target_link_libraries(UAV PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(UAV PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET UAV
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:UAV>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:UAV>
)
