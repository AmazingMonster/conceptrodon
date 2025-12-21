// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_H
#define CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_H
/******************************************************************************************************/




/******************************************************************************************************/
#include <cstddef>
#include <type_traits>
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_VALUE_RESULT has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_results/value.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_ROAD_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_proto_templates/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/define_proto_templates/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_ROAD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_synopsis_templates/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/define_synopsis_templates/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_VARIABLE_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_ROAD_VARIABLE_TEMPLATE has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_variable_templates/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_parameter_categories/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/define_parameter_categories/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_FUNCTION_NAME
#error "CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_FUNCTION_NAME   \
    KindredRightInterview
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_RESULT_INTEGRAL_TYPE
#error "CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_RESULT_INTEGRAL_TYPE has already been defined"
#endif

#define CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_RESULT_INTEGRAL_TYPE   \
    std::make_signed_t<size_t>
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Typella {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/typella/kindred_right_interview/kindred_right_interview.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_results/value.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_proto_templates/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_proto_templates/road.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_synopsis_templates/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_synopsis_templates/road.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_variable_templates/road.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_parameter_categories/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_FUNCTION_NAME
#undef CONCEPTRODON_TYPELLA_KINDRED_RIGHT_INTERVIEW_RESULT_INTEGRAL_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
