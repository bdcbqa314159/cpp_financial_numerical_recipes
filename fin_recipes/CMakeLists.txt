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
    src/american_option_approx.cpp
    src/exotic_options.cpp
    src/generic_binomial.cpp
    src/payoffs.cpp
    src/trinomial_trees.cpp
    src/bs_alternatives.cpp
    src/bond_options.cpp
    src/credit_risk.cpp
    src/term_structure_models.cpp
    src/binomial_term_structure_models.cpp
    src/ir_trees.cpp
)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
target_link_libraries(${PROJECT_NAME} PUBLIC GSL::gsl GSL::gslcblas)
