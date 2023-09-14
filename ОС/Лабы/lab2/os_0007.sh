#!/bin/bash

# Проверка наличия обязательного параметра PID процесса
if [ -z "$1" ]; then
  echo "Ошибка: не указан PID процесса."
  exit 1
fi

pid="$1"
fd="$2"

# Получение имени исполняемого файла
exe=$(readlink -f "/proc/$pid/exe")

# Получение PPID процесса
ppid=$(awk '/^PPid:/ {print $2}' "/proc/$pid/status")

# Получение списка открытых дескрипторов (fd) процесса
if [ -z "$fd" ]; then
  fd_list=$(ls -l "/proc/$pid/fd" | awk '{print $9}' | grep -oE '[0-9]+')
else
  fd_list=$(ls -l "/proc/$pid/fd" | awk -v fd="$fd" '{if ($11 == fd) print $9}' | grep -oE '[0-9]+')
fi

# Вывод информации
echo "Name: $exe"
echo "PID: $pid"
echo "PPID: $ppid"
echo "fd: $fd_list"