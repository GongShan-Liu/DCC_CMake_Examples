# 设置初始化变量
set(MOBU_VERSION 2018 CACHE STRING "MotionBuilder Version") # 可以在终端中通过键入以下内容来覆盖: -DMAX_VERSION = 2016
set(MOBU_LIB_DIR_NAME "lib/x64")
set(MOBU_INCLUDE_DIR_NAME "include")

# SDK路径
# set(MOBU_SDK_PATH "C:/Program Files/Autodesk/3ds Max ${MOBU_VERSION} SDK/maxsdk")
set(MOBU_SDK_PATH "C:/Program Files/Autodesk/MotionBuilder ${MOBU_VERSION}/OpenRealitySDK")
message("[Log] MotionBuilder SDK location: ${MOBU_SDK_PATH}")

# 在SDK路径查找头文件并返回目录
find_path(	MOBU_INCLUDE_DIR 	fbxsdk.h
			PATHS 				${MOBU_SDK_PATH} 
			PATH_SUFFIXES 		"${MOBU_INCLUDE_DIR_NAME}/"
			DOC					"MotionBuilder Include Path"
)
message("[Log] MotionBuilder include location:  ${MOBU_INCLUDE_DIR}")

# 在SDK路径查找库文件并返回目录
find_path(  MOBU_LIBRARY_DIR    fbsdk.lib
            PATHS               ${MOBU_SDK_PATH}
            PATH_SUFFIXES       "${MOBU_LIB_DIR_NAME}/"
            DOC                 "MotionBuilder Library Path"
)
message("[Log] MotionBuilder libs location: ${MOBU_LIBRARY_DIR}")

# 获取全部库文件到 MAX_LIBRARIES
file(GLOB MOBU_LIBRARY_LIBS "${MOBU_LIBRARY_DIR}/*.lib")

foreach(MOBU_LIB ${MOBU_LIBRARY_LIBS})
    get_filename_component(MOBU_LIBRARIE ${MOBU_LIB} NAME)
    set(MOBU_LIBRARIES ${MOBU_LIBRARIES} ${MOBU_LIBRARIE})
endforeach()

set(MOBU_LIBRARIES 
${MOBU_LIBRARIES}
opengl32.lib
glu32.lib
)

foreach(_LIB ${MOBU_LIBRARIES})
    message("[Log] MotionBuilder lib: ${_LIB}")
endforeach()

# # 设置sdk include路径
# include_directories("${MOBU_INCLUDE_DIR}")

# # 设置 sdk lib路径
# link_directories("${MOBU_LIBRARY_DIR}")

# # 设置链接到libs
# target_link_libraries(${PROJECT_NAME} ${MAX_LIBRARIES} )

# 通过循环设置每个编译选项 (_target)
function(MOBU_PLUGIN _target)
    if (WIN32)
        set_target_properties(
            ${_target}
            PROPERTIES
            OUTPUT_NAME ${_target}
        )

        set_target_properties(
            ${PROJECT_NAME}
            PROPERTIES
            LINK_FLAGS "/DYNAMICBASE:NO"
        )

    endif()

endfunction()



