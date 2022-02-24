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
		WebEngineWidgets
		)

if (Qt${QT_VERSION}WebEngineWidgets_FOUND)
	set(WEB_RESOURCE resourcesWeb.qrc)
	qt5_add_resources(WEB_RESOURCE_ADDED ${WEB_RESOURCE})

	add_library(Web SHARED
        	Web.cpp
        	Web.hpp
        	WebView.cpp WebView.hpp
        	WebPage.cpp WebPage.hpp
        	WebPopupWindow.cpp WebPopupWindow.hpp
        	${WEB_RESOURCE_ADDED}
            MainPage.cpp MainPage.hpp MainPage.ui)

	add_dependencies(Web FairWindSdk)
	target_link_libraries(Web PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::WebEngineWidgets Qt${QT_VERSION}::Positioning ${LIBFAIRWINDSDK})
	target_compile_options(Web PRIVATE ${COMPILE_OPTIONS})

	add_custom_command(
        TARGET Web
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Web>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:Web>
	)
else()
	message("Qt5WebEngineWidgets not available.")
endif()
