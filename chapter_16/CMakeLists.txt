project(chapter_16)

set(includes ./ ../fin_recipes/)
set(exe_1 asian_geo_average_call)
set(exe_2 asian_euro_lookback_call)
set(exe_3 simulating_exotic_payoffs)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} fin_recipes)

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})
target_link_libraries(${exe_2} fin_recipes)

add_executable(${exe_3} ${exe_3}.cpp)
target_include_directories(${exe_3} PUBLIC ${includes})
target_link_libraries(${exe_3} fin_recipes)
