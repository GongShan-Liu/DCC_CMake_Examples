@echo off

@REM 打印当前路径
echo %cd%


@REM @REM 先执行清理 CMake_Maya/build 和 CMake_Maya/plug-ins
rd /s /q %cd%\build;%cd%\plug-ins

@REM 设置构建maya版本 (不带小版本号)
set compile_maya_version=2020

@REM @REM 构建文件
"C:\Program Files\CMake\bin\cmake.exe"  -DMAYA_VERSION=%compile_maya_version% -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S %cd% -B %cd%/build/%compile_maya_version% -G "Visual Studio 15 2017" -T host=x64 -A x64 -DCMAKE_CONFIGURATION_TYPES=Release

@REM 调试或发布 --config Debug; --config Release
"C:\Program Files\CMake\bin\cmake.exe" --build %cd%/build/%compile_maya_version% --config Release --target ALL_BUILD


@REM pause