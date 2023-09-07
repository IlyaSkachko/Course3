@echo off

chcp 65001 > nul

echo Список параметров: %*


set "param1=%~1"
set "param2=%~2"
set "param3=%~3"

echo -- Параметр 1: %param1%
echo -- Параметр 2: %param2%
echo -- Параметр 3: %param3%

set /a sum = %param1% + %param2%
set /a sub = %param2% - %param1%
set /a mult = %param1% * %param2%
set /a div = %param3% / %param1% 
set /a exp = (%param2% - %param1%) * (%param1% - %param2%)

echo -- %param1% + %param2% = %sum%
echo -- %param1% * %param2% = %mult%
echo -- %param2% - %param1% = %sub%
echo -- %param3% / %param1% = %div%
echo -- (%param2% - %param1%) * (%param1% - %param2%) = %exp%



pause