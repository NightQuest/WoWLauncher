cmake_minimum_required(VERSION 3.15)
project(WoWLauncher)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

set(source_files
	src/WoWLauncher.cpp
	src/resource.h)
	
set(res_files
	src/res/WoWLauncher.rc
	src/res/logo.ico
	src/res/logo_black.ico)

set(all_source_files
	${source_files}
	${res_files})

if(MSVC)
	source_group("" FILES ${source_files})
	source_group("Resources" FILES ${res_files})
endif()

add_executable(WoWLauncher WIN32 ${all_source_files})

install(TARGETS WoWLauncher RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})