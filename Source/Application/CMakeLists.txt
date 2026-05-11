set(_exec_name OGFViewer)

set(_source_files
    OGFLoader.cpp
    OGFModel.cpp
    ChildView.cpp
    MainFrm.cpp
    OGFViewer.cpp
)

set(_rc_files 
    Resources/OGFViewer.rc
)

find_package(MFC)
if (NOT MFC_FOUND)
    message(CHECK_FAIL "MFC not exists")
endif()
set(CMAKE_MFC_FLAG 2)

add_executable(${_exec_name} WIN32 ${_source_files} ${_rc_files})

target_precompile_headers(${_exec_name} PRIVATE pch.h)

set_target_properties(${_exec_name} PROPERTIES 
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 17
)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

target_compile_definitions(${_exec_name} PRIVATE 
    WIN32
    _WINDOWS
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
    _AFXDLL
    _CRT_SECURE_NO_WARNINGS
    $<$<CONFIG:Debug>:GLEW_STATIC>
)

target_link_libraries(${_exec_name} PRIVATE 
    opengl32
    glu32
    glew-2.3.1
    nv_dds
)

add_custom_command(TARGET ${_exec_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Libraries/glext/lib/glext.dll
        $<TARGET_FILE_DIR:${_exec_name}>
    COMMENT "Копирование glext.dll в выходную папку"
)

