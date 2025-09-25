@echo off

@REM 打印当前路径
echo %cd%

@REM 检查maya的命令端口是否打开是否存在 如果打开就卸载插件
set MAYAPY_COMMAND_PORT=7072
netstat -ano | findstr "127.0.0.1:%MAYAPY_COMMAND_PORT%.*LISTENING" >nul
if %errorlevel%==0 (
    "c:\Program Files\Python310\python.exe" %cd%\maya_debug\unload_plugins.py
    echo "unlock plugins"
) else (
    echo "maya port=%MAYAPY_COMMAND_PORT% is close"
)

@REM 先执行清理 CMake_Maya/build 和 CMake_Maya/plug-ins
rd /s /q %cd%\build;%cd%\plug-ins

@REM 设置构建maya版本 (不带小版本号)
set compile_maya_version=2020

set maya_sdk_path="C:/Program Files/Autodesk/Maya_2020_4_devkit"
@REM set maya_sdk_path=""

@REM @REM 构建文件
"D:\Program Files\CMake\bin\cmake.exe" -DMAYA_SDK_LOCATION=%maya_sdk_path% -DMAYA_VERSION=%compile_maya_version% -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S %cd% -B %cd%/build/%compile_maya_version% -G "Visual Studio 15 2017" -T host=x64 -A x64 -DCMAKE_CONFIGURATION_TYPES=Release

@REM 调试或发布 --config Debug; --config Release
"D:\Program Files\CMake\bin\cmake.exe" --build %cd%/build/%compile_maya_version% --config Release --target ALL_BUILD


@REM 检查maya的命令端口是否打开是否存在 如果打开就执行测试代码，否则就打开maya
netstat -ano | findstr "127.0.0.1:%MAYAPY_COMMAND_PORT%.*LISTENING" >nul
if %errorlevel%==0 (
    "c:\Program Files\Python310\python.exe" %cd%\maya_debug\test_debug_maya.py
) else (
    echo "Open Maya"
    call %cd%\maya_debug\test_maya.bat
)
