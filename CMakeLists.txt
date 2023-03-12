cmake_minimum_required(VERSION 3.10)

project(FileDownloader VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include ${CMAKE_SOURCE_DIR}/include/autoconf.h")

find_package(Python COMPONENTS Interpreter Development REQUIRED)

find_package(CURL CONFIG REQUIRED)

file(GLOB SRCS
    ${PROJECT_SOURCE_DIR}/src/**.cpp
    ${PROJECT_SOURCE_DIR}/src/**.hpp
)

add_executable(FileDownloader ${SRCS})

set(CONFIG_FILENAME "${CMAKE_SOURCE_DIR}/prj.conf")
add_custom_command(
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    TARGET FileDownloader
    DEPENDS ${CONFIG_FILENAME}
)

add_custom_command(TARGET FileDownloader
PRE_BUILD
COMMAND ${Python_EXECUTABLE} scripts/autoconf.py
COMMENT "Generate autoconf headers"
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
include_directories(FileDownloader "include/")

target_link_libraries(FileDownloader PRIVATE CURL::libcurl)
