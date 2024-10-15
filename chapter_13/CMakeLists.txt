project(chapter_13)

set(includes ./ ../fin_recipes/)
set(exe_1 finite_diff_euro_american_put_explicit)
set(exe_2 finite_diff_euro_american_put_implicit)
# set(exe_3 american_div_option_binomial_approx)
# set(exe_4 futures_opt_bin_approx)
# set(exe_5 ccy_options_bin_approx)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} fin_recipes)

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})
target_link_libraries(${exe_2} fin_recipes)

# add_executable(${exe_3} ${exe_3}.cpp)
# target_include_directories(${exe_3} PUBLIC ${includes})
# target_link_libraries(${exe_3} fin_recipes)

# add_executable(${exe_4} ${exe_4}.cpp)
# target_include_directories(${exe_4} PUBLIC ${includes})
# target_link_libraries(${exe_4} fin_recipes)

# add_executable(${exe_5} ${exe_5}.cpp)
# target_include_directories(${exe_5} PUBLIC ${includes})
# target_link_libraries(${exe_5} fin_recipes)
