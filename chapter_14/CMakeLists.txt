project(chapter_14)

set(includes ./ ../fin_recipes/)
set(exe_1 euro_call_option_simulated)
set(exe_2 euro_call_delta_option_simulated)
set(exe_3 euro_option_generic)
set(exe_4 variance_reduction)
set(exe_5 variance_reduction_exotics)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} fin_recipes)

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})
target_link_libraries(${exe_2} fin_recipes)

add_executable(${exe_3} ${exe_3}.cpp)
target_include_directories(${exe_3} PUBLIC ${includes})
target_link_libraries(${exe_3} fin_recipes)

add_executable(${exe_4} ${exe_4}.cpp)
target_include_directories(${exe_4} PUBLIC ${includes})
target_link_libraries(${exe_4} fin_recipes)

add_executable(${exe_5} ${exe_5}.cpp)
target_include_directories(${exe_5} PUBLIC ${includes})
target_link_libraries(${exe_5} fin_recipes)
