cmake_minimum_required(VERSION 3.14)

project(tool-create-bmp-image LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(HEADERS
        BMPInfo.h
        ImageProvider/ImageProvider.h
        ImagePainter/ImagePainter.h
        utils/Material.h
)

set(SOURCES
        ImageProvider/ImageProvider.cpp
        ImagePainter/ImagePainter.cpp
        main.cpp
)

set(DRAFT_SOURCE
        Draft/Example.cpp
)

add_executable(tool-create-bmp-image
  ${HEADERS}
  ${SOURCES}
  ${DRAFT_SOURCE}
)

target_include_directories(tool-create-bmp-image PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tool-create-bmp-image Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)

include(GNUInstallDirs)
install(TARGETS tool-create-bmp-image
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
