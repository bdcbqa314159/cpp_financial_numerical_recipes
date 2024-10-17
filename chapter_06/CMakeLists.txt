project(chapter_6)

set(includes ./ ../fin_recipes/)
set(exe_1 setup_calculations)
set(exe_2 min_variance_portfolio)
# set(exe_3 ir_linear_interpolation)
# set(exe_4 term_structure_interpolated)
# set(exe_5 bond_calculation_term_structure)
# set(exe_6 linear_system_bond_calculations)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} GSL::gsl GSL::gslcblas)

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})
target_link_libraries(${exe_2} GSL::gsl GSL::gslcblas)

# add_executable(${exe_3} ${exe_3}.cpp)
# target_include_directories(${exe_3} PUBLIC ${includes})
# target_link_libraries(${exe_3} fin_recipes)

# add_executable(${exe_4} ${exe_4}.cpp)
# target_include_directories(${exe_4} PUBLIC ${includes})
# target_link_libraries(${exe_4} fin_recipes)

# add_executable(${exe_5} ${exe_5}.cpp)
# target_include_directories(${exe_5} PUBLIC ${includes})
# target_link_libraries(${exe_5} fin_recipes)

# add_executable(${exe_6} ${exe_6}.cpp)
# target_include_directories(${exe_6} PUBLIC ${includes})
# target_link_libraries(${exe_6} GSL::gsl GSL::gslcblas)
# # target_link_libraries(${exe_6} fin_recipes)
