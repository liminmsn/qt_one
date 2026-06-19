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

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets WebChannel)

file(GLOB_RECURSE WEB_RESOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/assets/web/*"
)

file(GLOB_RECURSE SRC_FILES 
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

set(CRAWLER_DIR "${CMAKE_SOURCE_DIR}/assets/crawler_tool")

if(APPLE)
    file(GLOB CRAWLER_BIN "${CRAWLER_DIR}/crawler")
    set_source_files_properties(${CRAWLER_BIN} PROPERTIES
        MACOSX_BUNDLE_LOCATION "Helpers"
    )

    file(GLOB_RECURSE CRAWLER_RESOURCES CONFIGURE_DEPENDS "${CRAWLER_DIR}/*")
    if(CRAWLER_BIN)
        list(REMOVE_ITEM CRAWLER_RESOURCES ${CRAWLER_BIN})
    endif()
    set_source_files_properties(${CRAWLER_RESOURCES} PROPERTIES
        MACOSX_BUNDLE_LOCATION "Resources/crawler_tool"
    )
    
    set_source_files_properties(
        "${CMAKE_SOURCE_DIR}/AppIcon.icns"
        PROPERTIES
        MACOSX_BUNDLE_LOCATION "Resources"
    )
endif()

add_executable(qt_one 
    main.cpp
    ${SRC_FILES}
    resources.qrc
    ${WEB_RESOURCES}
    ${CRAWLER_BIN}         
    ${CRAWLER_RESOURCES}   
    $<$<PLATFORM_ID:Darwin>:${CMAKE_SOURCE_DIR}/AppIcon.icns>
)

target_link_libraries(qt_one PRIVATE
    Qt6::Widgets
    Qt6::WebEngineWidgets
    Qt6::WebChannel
)

target_include_directories(qt_one PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

if(WIN32)
    target_sources(qt_one PRIVATE
        ${APP_RESOURCES}
    )

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
# 1. 强制开启 Bundle 属性
    set_target_properties(qt_one PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_ICON_FILE "AppIcon"
    )

    # 2. 🔥 暴力但 100% 完美的后置脚本：编译完主程序后，强行往 .app 里面灌文件
    add_custom_command(TARGET qt_one POST_BUILD
        # 创建缺失的文件夹
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:qt_one>/../Helpers"
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:qt_one>/../Resources"
        
        # 强行把底层二进制拷进去，并追加可执行权限
        COMMAND ${CMAKE_COMMAND} -E copy "${CRAWLER_DIR}/crawler" "$<TARGET_FILE_DIR:qt_one>/../Helpers/crawler"
        COMMAND chmod +x "$<TARGET_FILE_DIR:qt_one>/../Helpers/crawler"
        
        # 强行把依赖资源和图标拷进去
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CRAWLER_DIR}" "$<TARGET_FILE_DIR:qt_one>/../Resources/crawler_tool"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/AppIcon.icns" "$<TARGET_FILE_DIR:qt_one>/../Resources/AppIcon.icns"
        
        COMMENT "正在强行将爬虫程序和图标注入 macOS App Bundle..."
    )
endif()

set_target_properties(qt_one PROPERTIES OUTPUT_NAME "网络图片查找")