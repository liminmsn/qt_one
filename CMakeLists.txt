cmake_minimum_required(VERSION 3.10.0)
project(qt_one VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(WIN32)
list(APPEND CMAKE_PREFIX_PATH "E:/Qt/6.11.1/msvc2022_64")
elseif(APPLE)
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui OpenGL OpenGLWidgets)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

add_executable(qt_one 
    main.cpp
    ${SRC_FILES}
)

target_link_libraries(qt_one PRIVATE
    Qt6::Widgets
    Qt6::Gui
    Qt6::Core
)

target_include_directories(qt_one PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

target_sources(qt_one PRIVATE
    ${APP_RESOURCES}
)

if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE
        NAMES windeployqt
        HINTS "E:/Qt/6.11.1/msvc2022_64/bin"
    )

    add_custom_command(TARGET qt_one POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                --no-translations
                "$<TARGET_FILE:qt_one>"
        COMMENT "Running windeployqt..."
    )
    
elseif(APPLE)
target_sources(qt_one PRIVATE
    AppIcon.icns
)

qt_add_resources(APP_RESOURCES
    resources.qrc
)
set_source_files_properties(
    AppIcon.icns
    PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources
)

# Ensure the target is built as a macOS .app bundle and set its icon
set_target_properties(qt_one PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_ICON_FILE AppIcon.icns
)
endif()



set_target_properties(qt_one PROPERTIES OUTPUT_NAME "编辑器")