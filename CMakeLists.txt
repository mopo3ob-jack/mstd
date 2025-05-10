cmake_minimum_required(VERSION 3.12)

project(
	"mstd" VERSION 1.0.0
	DESCRIPTION "Vector and memory utilities"
	HOMEPAGE_URL "https://github.com/mopo3ob-jack/mstd"
)

include(GNUInstallDirs)

add_library(mstd INTERFACE)

target_include_directories(mstd INTERFACE inc/)
set_target_properties(mstd PROPERTIES CXX_STANDARD 20)

install(DIRECTORY inc/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
