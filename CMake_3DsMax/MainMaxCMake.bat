@REM @REM 先执行清理 CMake_3DsMax/build 和 CMake_3DsMax/plug-ins
rd /s /q %cd%\build;%cd%\plug-ins

@REM 设置构建3DsMax版本、windows sdk版本、toolset版本
set compile_max_version=2020
set system_sdk_version="10.0.17134.0"
set toolset_version="v141"

@REM @REM 构建文件
"C:\Program Files\CMake\bin\cmake.exe" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S %cd% -B %cd%/build -DMAX_VERSION=%compile_max_version% -DCMAKE_SYSTEM_VERSION=%system_sdk_version% -DCMAKE_GENERATOR_TOOLSET=%toolset_version% -DCMAKE_CONFIGURATION_TYPES=Release

@REM 调试或发布 --config Debug; --config Release
"C:\Program Files\CMake\bin\cmake.exe" --build %cd%/build --config Release --target ALL_BUILD