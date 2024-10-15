project(fin_recipes)

set(includes includes/)
set(sources
    src/date.cpp
    src/pv_calculations.cpp
    # src/irr_calculations.cpp
    src/bond_pricing.cpp
    src/term_ir.cpp
    src/term_structure.cpp
    src/term_structure_flat.cpp
    src/term_structure_interpolated.cpp
    src/futures.cpp
    src/binomial_option_pricing.cpp
    src/option_pricing_bs.cpp
    src/norm_dist.cpp
    src/warrants.cpp
    src/extending_bs.cpp
    src/option_pricing_binomial_approx.cpp
    src/finite_differences.cpp
    src/option_pricing_simulation.cpp
)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
target_link_libraries(${PROJECT_NAME} PUBLIC GSL::gsl GSL::gslcblas)
