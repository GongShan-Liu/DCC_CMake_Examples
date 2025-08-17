# 设置项目名称
project(TestMeshObj)

# 查找testDeformer下全部.cpp和.h文件
file(GLOB SRCS "*.cpp" "*.h" "*.aps" "*.def" "*.rc")

# 预处理器包含文件搜索目录列表
include_directories(${MAX_INCLUDE_DIR})

# 链接器搜索目录列表
link_directories(${MAX_LIBRARY_DIR})

# 已经指定的 project() 名称 - PROJECT_NAME 变量一开始就存在
# 构建库 (SHARED = dynamic library = dll)
add_library(${PROJECT_NAME} SHARED ${SRCS}) 


# 为项目指定库
target_link_libraries(${PROJECT_NAME} ${MAX_LIBRARIES}) # 将程序与库链接起来

MAX_PLUGIN(${PROJECT_NAME} ".dlo") # FindMaya.cmake 模块中定义的函数 MAX_PLUGIN(项目名, 插件后缀名)

