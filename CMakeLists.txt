cmake_minimum_required(VERSION 3.15)
project(WoWLauncher)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

set(source_files
	src/WoWLauncher.cpp)


add_executable(WoWLauncher WIN32 ${source_files})

install(TARGETS WoWLauncher RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})