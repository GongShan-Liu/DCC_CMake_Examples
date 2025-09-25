# 核心CMakeLists.txt文件，其中包含外部模块和cmake命令

# 设置cmake版本
# cmake_minimum_required(VERSION 3.30.2) 

# 防止CMake的自动重新生成 (在vsc构建需要设置vsc的cmake工具的自动构建)
set(CMAKE_SUPPRESS_REGENERATION true)

# 为不同类型的编译产品指定的二进制输出目录-运行时
if (WIN32)
    # 构建路径
    
    # 输出路径
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/plug-ins/Release/${MAYA_VERSION})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/plug-ins/Debug/${MAYA_VERSION})
else()
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/plug-ins/${MAYA_VERSION})
endif()


# 包含用于 "include()" 和 "find_package()" 命令的路径的系统变量 (设置cmake模块的路径)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


# 从外部模块查找和加载指令 (优先搜索Find<PackageName>.cmake, 没找到再搜索<PackageName>-config.cmake)
find_package(Maya REQUIRED)

# 创建将包含在生成的解决方案（或生成文件）中的用户项目列表
# CHACHE STRING 指出一个单独的项目，它将是cmake生成和编译的唯一项目
# 当我们处理数十个项目时，这很有用，因为我们不想等到cmake编译完它们
# 例如:  >> cmake -G "Unix Makefiles" -DMAYA_PROJECT testCommand  -  将生成一个只处理testCommand项目的makefile
set(MAYA_PROJECT
	# testDeformer
	testCommand
	CACHE STRING "Maya Project")

# 在这里将子目录添加到构建中
# projects/${MAYA_PRJ} 是一个相对目录，源CMakeLists.txt和代码文件位于其中
foreach(MAYA_PRJ ${MAYA_PROJECT})
	add_subdirectory(projects/${MAYA_PRJ}) 
endforeach()

