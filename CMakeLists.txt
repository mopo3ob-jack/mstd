cmake_minimum_required(VERSION 3.12)

project(
	"mstd" VERSION 1.0.0
	DESCRIPTION "Vector and memory utilities"
	HOMEPAGE_URL "https://github.com/mopo3ob-jack/mstd"
)

add_library(mstd INTERFACE)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
target_include_directories(mstd INTERFACE inc/)
set_target_properties(mstd PROPERTIES CXX_STANDARD 20)

add_executable(main)
target_sources(main PRIVATE main.cpp)
set_target_properties(main PROPERTIES CXX_STANDARD 20)
target_link_libraries(main PRIVATE mstd)
