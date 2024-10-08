project(fin_recipes)

set(includes includes/)
set(sources
    src/cash_flow_pv_discrete.cpp
)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})