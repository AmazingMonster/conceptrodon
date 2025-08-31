// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_H
#define CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_H
/******************************************************************************************************/




/******************************************************************************************************/
#include <cstddef>
#include <type_traits>
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_VALUE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/value.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_proto_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_VARIABLE_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_VARIABLE_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_variable_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_FUNCTION_NAME
#error "CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_FUNCTION_NAME   \
    TerseIndependentFind
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_PARAMETERS_IDENTIFIER
#error "CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_PARAMETERS_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_PARAMETERS_IDENTIFIER   \
    Predicates
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_RESULT_INTEGRAL_TYPE
#error "CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_RESULT_INTEGRAL_TYPE has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_RESULT_INTEGRAL_TYPE   \
    std::make_signed_t<size_t>
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Pagelis {
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
    ... CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_PARAMETERS_IDENTIFIER
>
struct CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_FUNCTION_NAME
{
#include "conceptrodon/microbiota/pagelis/terse_independent_find/terse_independent_find.hpp"
};
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/value.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_variable_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_FUNCTION_NAME
#undef CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_PARAMETERS_IDENTIFIER
#undef CONCEPTRODON_PAGELIS_TERSE_INDEPENDENT_FIND_RESULT_INTEGRAL_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
