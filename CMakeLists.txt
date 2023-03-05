cmake_minimum_required(VERSION 3.10)

project(FileDownloader VERSION 0.1)

#set(CMAKE_PREFIX_PATH "C:/Users/Andy/Documents/Libraries/curl-7.86.0/")

find_package(CURL CONFIG REQUIRED)


file(GLOB SRCS
    ${PROJECT_SOURCE_DIR}/src/**.cpp
)

add_executable(FileDownloader ${SRCS})

target_link_libraries(FileDownloader PRIVATE CURL::libcurl)