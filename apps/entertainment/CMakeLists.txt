set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)

find_package(Qt${QT_VERSION} REQUIRED COMPONENTS
		Core
		Gui
		Network
		Widgets
		WebSockets
		Positioning
		Multimedia
		MultimediaWidgets
		)

if (Qt${QT_VERSION}Multimedia_FOUND AND Qt${QT_VERSION}MultimediaWidgets_FOUND)

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
	target_link_libraries(Entertainment PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Multimedia Qt${QT_VERSION}::MultimediaWidgets Qt${QT_VERSION}::Network Qt${QT_VERSION}::Xml Qt${QT_VERSION}::Positioning ${LIBFAIRWINDSDK})
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
