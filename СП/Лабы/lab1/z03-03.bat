@echo off

chcp 65001 > nul

echo Список параметров: %*


set "param1=%~1"
set "param2=%~2"
set "param3=%~3"
set "param4=%~4"

echo -- Параметр 1: %param1%
echo -- Параметр 2: %param2%
echo -- Параметр 3: %param3%
echo -- Параметр 4: %param4%

pause
