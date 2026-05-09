set(_library_name glext)
set(_shared_path ${CMAKE_CURRENT_SOURCE_DIR}/lib/${_library_name}.dll)

add_library(${_library_name} STATIC IMPORTED GLOBAL)

target_include_directories(${_library_name} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(${_library_name} PROPERTIES
    IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/lib/glext.lib
    IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/lib/glext.lib
    MAP_IMPORTED_CONFIG_MINSIZEREL Release
    MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
)

get_target_property(${_library_name}_INCLUDE_DIR ${_library_name} INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "${_library_name} include dir: ${${_library_name}_INCLUDE_DIR}")
