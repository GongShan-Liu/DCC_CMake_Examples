cd /d %~dp0

set MAYA_VERSION=2020
set MAYA_PLUG_IN_PATH=%MAYA_PLUG_IN_PATH%;%cd%\..\plug-ins\Release\%MAYA_VERSION%

"C:\Program Files\Autodesk\Maya%MAYA_VERSION%\bin\maya.exe" -script "%cd%\maya_start_cmd.mel"