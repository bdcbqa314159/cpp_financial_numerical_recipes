project(chapter_13)

set(includes ./ ../fin_recipes/)
set(exe_1 finite_diff_euro_american_put_explicit)
set(exe_2 finite_diff_euro_american_put_implicit)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} fin_recipes)

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})
target_link_libraries(${exe_2} fin_recipes)
