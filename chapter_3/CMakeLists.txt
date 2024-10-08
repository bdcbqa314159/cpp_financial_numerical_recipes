project(chapter_3)

set(includes ./ ../fin_recipes/)
set(exe_1 pv)
set(exe_2 irr)
# set(exe_3 main_date)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} fin_recipes)

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})
target_link_libraries(${exe_2} fin_recipes)

# add_executable(${exe_3} ${exe_3}.cpp date.cpp)
# target_include_directories(${exe_3} PUBLIC ${includes})