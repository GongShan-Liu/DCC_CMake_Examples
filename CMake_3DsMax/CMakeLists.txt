# 设置 cmake版本
cmake_minimum_required(VERSION 3.30.2)


# 防止CMake的自动重新生成 (在vsc构建需要设置vsc的cmake工具的自动构建)
set(CMAKE_SUPPRESS_REGENERATION true)

# 设置windows sdk 版本 和 工具集版本
# set(CMAKE_SYSTEM_VERSION ${3DSMAX_WINDOWS_SDK_VERSION})
# set(CMAKE_GENERATOR_TOOLSET ${3DSMAX_WINDOWS_PLATFORM_TOOLSET})

message("[log] CMAKE_SYSTEM_VERSION = ${CMAKE_SYSTEM_VERSION}")
message("[log] CMAKE_GENERATOR_TOOLSET = ${CMAKE_GENERATOR_TOOLSET}")


# 设置输出路径
if (WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/plug-ins/Release/${MAX_VERSION})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/plug-ins/Debug/${MAX_VERSION})
endif()

# 包含用于 "include()" 和 "find_package()" 命令的路径的系统变量 (设置cmake模块的路径)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


# 从外部模块查找和加载指令 (优先搜索Find<PackageName>.cmake, 没找到再搜索<PackageName>-config.cmake)
find_package(Max REQUIRED)

set(MAX_PROJECTS
    TestMeshObj
	CACHE STRING "3DsMax Project")

foreach(MAX_PROJECT ${MAX_PROJECTS})
	add_subdirectory(projects/${MAX_PROJECT}) 
endforeach()



