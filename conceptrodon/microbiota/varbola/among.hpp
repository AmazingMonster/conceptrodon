// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_VARBOLA_AMONG_H
#define CONCEPTRODON_VARBOLA_AMONG_H
/******************************************************************************************************/




/******************************************************************************************************/
#include <cstddef>
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_VALUE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/value.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PLAN_PROTO_TEMPLATE has already been defined"
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

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_VARBOLA_AMONG_FUNCTION_NAME
#error "CONCEPTRODON_VARBOLA_AMONG_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_VARBOLA_AMONG_FUNCTION_NAME   \
    Among
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Varbola {
/******************************************************************************************************/


/******************************************************************************************************/
#include "conceptrodon/microbiota/varbola/among/among.hpp"
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
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_VARBOLA_AMONG_FUNCTION_NAME
/******************************************************************************************************/



/******************************************************************************************************/
#endif 
/******************************************************************************************************/
