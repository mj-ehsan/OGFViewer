set(_library_name nv_dds)

add_library(${_library_name} STATIC 
    nv_dds.cpp
)

set_target_properties(${_library_name} PROPERTIES
    CMAKE_GENERATOR_PLATFORM x86
)

target_include_directories(${_library_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${_library_name} PRIVATE
    glext
)

get_target_property(${_library_name}_INCLUDE_DIR ${_library_name} INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "${_library_name} include dir: ${${_library_name}_INCLUDE_DIR}")