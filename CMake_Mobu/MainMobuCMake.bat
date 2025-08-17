@REM 先执行清理
rd /s /q build;plug-ins

@REM 设置构建MotionBuilder版本 (不带小版本号)
set compile_mobu_version=2020

"C:\Program Files\CMake\bin\cmake.exe" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S %cd% -B %cd%/build -DMOBU_VERSION=%compile_mobu_version% -DCMAKE_CONFIGURATION_TYPES=Release

"C:\Program Files\CMake\bin\cmake.exe" --build %cd%/build --config Release --target ALL_BUILD