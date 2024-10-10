project(fin_recipes)

set(includes includes/)
set(sources
    src/date.cpp
    src/pv_calculations.cpp
    # src/irr_calculations.cpp
    src/bond_pricing.cpp
    src/term_ir.cpp
)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
