project(chapter_1)

set(includes ./ ../fin_recipes/)
set(exe_1 test)
set(exe_2 explicit_program)
set(exe_3 main_date)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})

add_executable(${exe_3} ${exe_3}.cpp)
target_include_directories(${exe_3} PUBLIC ${includes})
target_link_libraries(${exe_3} PUBLIC fin_recipes)