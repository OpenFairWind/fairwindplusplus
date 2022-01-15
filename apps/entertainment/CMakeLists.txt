set(QT_VERSION 5)
find_package(Qt5 COMPONENTS Multimedia MultimediaWidgets)
if (Qt5Multimedia_FOUND AND Qt5MultimediaWidgets_FOUND)

	set(ENTERTAINMENT_RESOURCE resourcesEntertainment.qrc)
	qt5_add_resources(ENTERTAINMENT_RESOURCE_ADDED ${ENTERTAINMENT_RESOURCE})

	add_library(Entertainment SHARED
        	Entertainment.cpp
        	Entertainment.hpp
			MainPage.cpp MainPage.hpp MainPage.ui
        	PlayerControls.cpp PlayerControls.hpp PlayerControls.ui
        	PlaylistModel.cpp PlaylistModel.hpp
        	HistogramWidget.cpp HistogramWidget.hpp
        	VideoWidget.cpp VideoWidget.hpp
        	${ENTERTAINMENT_RESOURCE_ADDED}
            )

	add_dependencies(Entertainment FairWindSdk)
	target_link_libraries(Entertainment PRIVATE Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Network Qt5::Xml  ${LIBFAIRWINDSDK})
	target_compile_options(Entertainment PRIVATE ${COMPILE_OPTIONS})

	add_custom_command(
        	TARGET Entertainment
        	POST_BUILD
        	COMMAND ${CMAKE_COMMAND} -E copy
        	$<TARGET_FILE:Entertainment>
        	$<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Entertainment>
	)
else()
	message("Qt5Multimedia and Qt5MultimediaWidgets not available.")
endif()
