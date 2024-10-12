cmake_minimum_required(VERSION 3.30)

project(cpp_financial_numerical_recipes LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(GSL REQUIRED)

add_subdirectory(fin_recipes)

add_subdirectory(chapter_1)
add_subdirectory(chapter_2)
add_subdirectory(chapter_3)
add_subdirectory(chapter_4)
add_subdirectory(chapter_5)
