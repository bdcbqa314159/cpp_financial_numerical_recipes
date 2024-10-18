project(chapter_6)

set(includes ./ ../fin_recipes/)
set(exe_1 setup_calculations)
set(exe_2 min_variance_portfolio)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} GSL::gsl GSL::gslcblas)

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})
target_link_libraries(${exe_2} GSL::gsl GSL::gslcblas)
