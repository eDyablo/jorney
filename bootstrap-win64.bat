@echo off
set startDir=%cd%
set scriptDir=%~dp0
cd %scriptDir%\jamplus
call git submodule init
call git submodule update
call bootstrap-win64.bat
cd %startDir%