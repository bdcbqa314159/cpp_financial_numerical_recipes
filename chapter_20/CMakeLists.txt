project(chapter_20)

set(includes ./ ../fin_recipes/)
set(exe_1 bond_put_options)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} fin_recipes)
