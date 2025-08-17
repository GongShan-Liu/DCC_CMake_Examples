# 本项目是方便DCC 开发SDK C+插件快速配置CMake文件的参考案例
- 编译环境都是在windows系统下完成
- 使用 VSCode作为项目的开发工具
- 安装好CMake, 本项目测试版本是4.1.0 (根据实际需求换不同版本也可行)
- 本项目测试的dcc软件都是 2020 版本
# 1. CMake配置Maya SDK开发
- 本cmake案例参考项目: https://github.com/volodinroman/maya-cmake
- 需要本地安装好对应的maya版本软件
- 下载对应的maya版本SDK 并放置到 CMake_Maya/maya2018 (不用带版本号)
    - 例如: maya2018.7 sdk下载链接 (根据实际修改下载路径的版本号即可下载对应的版本sdk)
      - https://autodesk-adn-transfer.s3-us-west-2.amazonaws.com/ADN+Extranet/M%26E/Maya/devkit+2018/Autodesk_Maya_2018_7_Update_DEVKIT_Windows.zip
      - https://autodesk-adn-transfer.s3-us-west-2.amazonaws.com/ADN+Extranet/M%26E/Maya/devkit+2018/Autodesk_Maya_2018_7_Update_DEVKIT_Mac.dmg
      - https://autodesk-adn-transfer.s3-us-west-2.amazonaws.com/ADN+Extranet/M%26E/Maya/devkit+2018/Autodesk_Maya_2018_7_Update_DEVKIT_Linux.tgz
    - 2020.4
      - https://autodesk-adn-transfer.s3-us-west-2.amazonaws.com/ADN+Extranet/M%26E/Maya/devkit+2020/Autodesk_Maya_2020_4_Update_DEVKIT_Windows.zip
- CMake_Maya/MainMayaCMake.bat 运行bat 即可执行 修改 compile_maya_version变量的版本号 即可根据情况编译
- CMake_Maya/CMakeLists.txt 是配置maya的主cmake文件
- cmake/FindMaya.cmake 是配置maya插件的核心cmake文件
- 编译成功之后的测试:
  - 在maya的Plug-in Manager中加载 编译好的插件 CMake_Maya\plug-ins\Release\2020\testCommandPlugin.mll
  - 在脚本编辑器窗口 MEL窗口中 输入 runTest 并运行就会打印信息 // Hello, Maya! // 就表示测试成功

# 2. CMake配置3DsMax SDK开发
- 本cmake案例参考项目: https://github.com/sideeffects/HoudiniEngineFor3dsMax
- 需要本地安装好对应的max版本软件和max SDK版本
- 尽可能按照官方sdk编译环境安装好 windows sdk版本和工具集版本
  - 官方编译参考: https://help.autodesk.com/view/3DSMAX/2020/ENU/?guid=__developer_about_the_3ds_max_sdk_sdk_requirements_html
  - 最好按官方说明 在 VS 安装好 Max SDK开发的向导插件 AppWizard
    - https://help.autodesk.com/view/3DSMAX/2020/ENU/?guid=__developer_3ds_max_sdk___the_learning_path_installing_the_plug_in_wizard_ap_html
    - https://zhuanlan.zhihu.com/p/659561496
- CMake_3DsMax/MainMaxCMake.bat 运行 bat 即可执行
  - compile_max_version指定 max版本
  - system_sdk_version指定 windows SDK版本 (必须在系统中安装好对应的sdk版本, Visual Studio Installer可以安装到所需版本)
  - toolset_version指定 工具集版本
- CMake_Max/CMakeLists.txt 是配置3DsMax的主cmake文件
- cmake/FindMax.cmake 是配置3DsMax插件的核心cmake文件
  - 函数 MAX_PLUGIN(项目名, 插件后缀名) 其中插件后缀名需要根据编译的插件类型填写扩展名
  - 3DsMax插件并不是统一编译成dll，它是根据编译类型编译成不同的插件扩展名
    - 官方参考: https://help.autodesk.com/view/3DSMAX/2020/ENU/?guid=__developer_writing_plug_ins_creating_a_plug_in_project_manually_creating_a_new_plug_in__plug_in_file_extensions_html
- 编译成功之后的测试:
  - 把编译好的插件 CMake_3DsMax\plug-ins\Release\2020\TestMeshObj.dlo 复制到max安装路径 ...\3ds Max 2020\Plugins 下
  - 能正常打开3DsMax 在创建几何体下找到MyMesh选项，选择到该选项之后会显示 TestMeshObj 可创建对象就表示测试成功 (因为测试项目代码没有实际对象代码, 所以无法创建出几何体)
  
# 3. CMake配置MotionBuilder SDK开发
- 需要本地安装好对应的MotionBuilder版本软件
- CMake_Mobu/MainMobuCMake.bat 运行 bat 即可执行
  - compile_mobu_version指定 MotionBuilder版本
- CMake_Mobu/CMakeLists.txt 是配置MotionBuilder的主cmake文件
- cmake/FindMobu.cmake 是配置MotionBuilder插件的核心cmake文件
- 编译成功之后的测试:
  - 把编译好的插件 CMake_Mobu\plug-ins\Release\2020\orconstraintposition.dll 复制到MotionBuilder安装路径 ...\MotionBuilder 2020\bin\x64\plugins 下
  - 在Navigator > Scene Browser Filters > Constraints > insert Constraint 找到  "TestOR - Position from Position" 点击创建就表示测试成功