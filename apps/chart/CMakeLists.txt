
set(CHART_RESOURCE resourcesChart.qrc)
qt5_add_resources(CHART_RESOURCE_ADDED ${CHART_RESOURCE})

add_library(Chart SHARED
        Chart.cpp
        Chart.hpp
        ${CHART_RESOURCE_ADDED}
        )

add_dependencies(Chart QGeoView)
add_dependencies(Chart FairWindSdk)
target_link_libraries(Chart PRIVATE Qt5::Widgets Qt5::Network  ${LIBFAIRWINDSDK})
target_compile_options(Chart PRIVATE ${COMPILE_OPTIONS})

add_custom_command(
        TARGET Chart
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Chart>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Chart>
)
