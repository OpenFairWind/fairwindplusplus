
set(IMSF_RESOURCE resourcesIMSF.qrc)
qt5_add_resources(IMSF_RESOURCE_ADDED ${IMSF_RESOURCE})

add_library(IMSF SHARED
        IMSF.cpp
        IMSF.hpp
        ${IMSF_RESOURCE_ADDED}
        )

add_dependencies(IMSF FairWindSdk)
target_link_libraries(IMSF PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(IMSF PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET IMSF
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:IMSF>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:IMSF>
)
