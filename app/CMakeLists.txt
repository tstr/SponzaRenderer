#
#	Application
#

SET(src_list

	src/main.cpp
	src/application.cpp
	src/application.h
	
	src/scene/modelimporter.h
	src/scene/modelimporter.cpp
	src/scene/camera.h
	src/scene/camera.cpp
	
	src/helpers/geometry.cpp
	src/helpers/geometry.h
	src/helpers/appinfo.h
	src/helpers/appinfo.cpp

	src/ui/ui.h
	src/ui/ui.cpp
	src/ui/ui_draw.cpp
	src/ui/imgui/imconfig.h
	src/ui/imgui/imgui.h
	src/ui/imgui/imgui.cpp
	src/ui/imgui/imgui_draw.cpp
	src/ui/imgui/imgui_internal.h

	src/ui/debugmenu.h
	src/ui/debugmenu.cpp
	src/ui/commandconsole.h
	src/ui/commandconsole.cpp
)

ADD_EXECUTABLE_TSE(
	application
	"${src_list}"
)

ASSIGN_SOURCE_GROUPS(${src_list})

TARGET_LINK_LIBRARIES(application PUBLIC tsengine)

#Config.ini
set(TS_ASSETS_PATH "${PROJECT_SOURCE_DIR}/assets")

CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/config.ini"
	"${CMAKE_CURRENT_BINARY_DIR}/config.ini"
)

set(TS_ASSETS_PATH "../assets")

CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/config.ini"
	"${PROJECT_BINARY_DIR}/staging/config.ini"
)
INSTALL(FILES "${PROJECT_BINARY_DIR}/staging/config.ini" DESTINATION ${TS_BINARY_INSTALL})
