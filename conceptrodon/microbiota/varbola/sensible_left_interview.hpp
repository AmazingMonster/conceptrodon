// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_H
#define CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_H
/******************************************************************************************************/




/******************************************************************************************************/
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

#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_proto_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/define_proto_templates/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_RAIL_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/rail.hpp"
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
#ifdef CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_FUNCTION_NAME
#error "CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_FUNCTION_NAME   \
    SensibleLeftInterview
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE
#error "CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE has already been defined"
#endif

#define CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE   \
    std::make_signed_t<size_t>
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Varbola {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/varbola/sensible_left_interview/sensible_left_interview.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/value.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_variable_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_FUNCTION_NAME
#undef CONCEPTRODON_VARBOLA_SENSIBLE_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
