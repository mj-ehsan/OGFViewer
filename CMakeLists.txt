cmake_minimum_required(VERSION 3.30)

project(OGFViewer_Solution)

add_subdirectory("Libraries/nv_dds")
add_subdirectory("Libraries/glew-2.3.1")
add_subdirectory("Libraries/glext")

add_subdirectory("Source/Application")