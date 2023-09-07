@echo off

chcp 65001 > nul

echo -- имя этого bat-файла: %~nx0

for %%F in ("%~nx0") do set FILENAME=%%~tF
echo -- этот файл создан: %FILENAME%

echo -- путь к файлу bat: %cd%

pause