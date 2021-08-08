
set(WEATHER_RESOURCE resourcesWeather.qrc)
qt5_add_resources(WEATHER_RESOURCE_ADDED ${WEATHER_RESOURCE})

add_library(Weather SHARED
        Weather.cpp
        Weather.hpp
        ${WEATHER_RESOURCE_ADDED}
        )

add_dependencies(Weather FairWindSdk)
target_link_libraries(Weather PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(Weather PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Weather
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Weather>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Weather>
)
