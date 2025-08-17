# 设置初始化变量
set(MAX_VERSION 2018 CACHE STRING "3DsMax Version") # 可以在终端中通过键入以下内容来覆盖: -DMAX_VERSION = 2016
set(MAX_LIB_DIR_NAME "lib/x64/Release")
set(MAX_INCLUDE_DIR_NAME "include")

# SDK路径
set(MAX_SDK_PATH "C:/Program Files/Autodesk/3ds Max ${MAX_VERSION} SDK/maxsdk")
message("[Log] Max SDK location: ${MAX_SDK_PATH}")

# 在SDK路径查找头文件并返回目录
find_path(	MAX_INCLUDE_DIR 	istdplug.h
			PATHS 				${MAX_SDK_PATH} 
			PATH_SUFFIXES 		"${MAX_INCLUDE_DIR_NAME}/"
			DOC					"Max Include Path"
)
message("[Log] Max include location:  ${MAX_INCLUDE_DIR}")

# 在SDK路径查找库文件并返回目录
find_path(  MAX_LIBRARY_DIR    core.lib
            PATHS               ${MAX_SDK_PATH}
            PATH_SUFFIXES       "${MAX_LIB_DIR_NAME}/"
            DOC                 "Max Library Path"
)
message("[Log] Max libs location: ${MAX_LIBRARY_DIR}")

# 获取全部库文件到 MAX_LIBRARIES
file(GLOB MAX_LIBRARY_LIBS "${MAX_LIBRARY_DIR}/*.lib")

foreach(MAX_LIB ${MAX_LIBRARY_LIBS})
    get_filename_component(MAX_LIBRARIE ${MAX_LIB} NAME)
    set(MAX_LIBRARIES ${MAX_LIBRARIES} ${MAX_LIBRARIE})
    message("[Log] Max lib: ${MAX_LIBRARIE}")
endforeach()

# # 设置sdk include路径
# include_directories("${MAX_INCLUDE_DIR}")

# # 设置 sdk lib路径
# link_directories("${MAX_LIBRARY_DIR}")

# # 设置链接到libs
# target_link_libraries(${PROJECT_NAME} ${MAX_LIBRARIES} )

# 通过循环设置每个编译选项 (_target)
function(MAX_PLUGIN _target _suffix)
    if (WIN32)
        set_target_properties(
            ${_target}
            PROPERTIES
            OUTPUT_NAME ${_target}
            SUFFIX ${_suffix}
        )

        target_compile_definitions(${_target} PRIVATE
            -DUNICODE -D_UNICODE
        )
    endif()

endfunction()



