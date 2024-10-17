project(chapter_17)

set(includes ./ ../fin_recipes/)
set(exe_1 generic_binomial_calculations)
set(exe_2 generic_binomial_delta_calculations)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} fin_recipes)

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})
target_link_libraries(${exe_2} fin_recipes)
