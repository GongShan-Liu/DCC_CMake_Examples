# 插件名称
project(testDeformerPlugin) #project name


# 查找testDeformer下全部.cpp和.h文件
file(GLOB SRCS "*.cpp" "*.h")

# 预处理器包含文件搜索目录列表
include_directories(${MAYA_INCLUDE_DIR})

# 链接器搜索目录列表
link_directories(${MAYA_LIBRARY_DIR})

# 已经指定的 project() 名称 - PROJECT_NAME 变量一开始就存在
# 构建库 (SHARED = dynamic library = dll)
add_library(${PROJECT_NAME} SHARED ${SRCS}) 

# 为项目指定库
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES}) # 将程序与库链接起来

MAYA_PLUGIN(${PROJECT_NAME}) # FindMaya.cmake 模块中定义的函数


# destination - 指定文件将安装到的磁盘目录
# targets - 想要安装什么 | PROJECT_NAME - 是插件编译的名称 | MAYA_TARGET_TYPE - 二进制文件的类型 (DLL, EXE)
# install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION plug-ins) # 仅当使用时才有效 "cmake --build . --config Release --target Install"


