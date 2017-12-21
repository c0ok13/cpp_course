# Минимальная версия CMake: 3.8
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Имя проекта: sfml-lab-1

project(cpp-samples)


# Подкаталог 00 содержит ещё один CMakeLists.txt

add_subdirectory(sfml1.1)
add_subdirectory(sfml1.2)
add_subdirectory(sfml1.3)