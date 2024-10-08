// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_H
#define CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_H
/******************************************************************************************************/




/******************************************************************************************************/
#include <type_traits>
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER
#error "CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_identifiers/separator.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_VALUE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/value.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_proto_templates/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_VARIABLE_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_VARIABLE_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_variable_templates/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_FUNCTION_NAME
#error "CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_FUNCTION_NAME   \
    LeftInterview
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_PARAMETER_IDENTIFIER   \
    Predicate
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_INTERVIEWER_IDENTIFIER
#error "CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_INTERVIEWER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_INTERVIEWER_IDENTIFIER   \
    Interviewer
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE
#error "CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE   \
    std::make_signed_t<size_t>
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Moldiae {
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY
    CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_FUNCTION_NAME
{
    template
    < 
        CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
        CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_INTERVIEWER_IDENTIFIER
    >
    struct CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE
    {
        struct CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER
        {
#include "conceptrodon/microbiota/moldiae/left_interview/left_interview.hpp"
        };

        template
        <
            CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
            ...Agreements
        >
        using CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
        =   CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER 
            ::template CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE <Agreements...>;

        template
        <
            CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
            ...Args
        >
        static constexpr auto CONCEPTRODON_NUCLEOLUS_MOLD_VARIABLE_TEMPLATE
        =   CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER 
            ::template CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE <Args...>
            ::  CONCEPTRODON_NUCLEOLUS_VALUE_RESULT ;
    };

    template
    <
        CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
        ...Agreements
    >
    using CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
    = CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE <Agreements...>;

};
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_identifiers/separator.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_results/value.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_variable_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_FUNCTION_NAME
#undef CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_PARAMETER_IDENTIFIER
#undef CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_INTERVIEWER_IDENTIFIER
#undef CONCEPTRODON_MOLDIAE_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
