// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_FUNCTION_NAME
#error "CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_FUNCTION_NAME has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE
#error "CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_LENGTH
#error "CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_LENGTH has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT has already been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template 
<
    CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY 
    Predicate,

    CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY 
    Interviewer,

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS   \
    CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    , CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY 
    ...RestElements

>
struct CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_FUNCTION_NAME
<
    Predicate,
    Interviewer,

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    , RestElements...
> 
{
    static constexpr CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE
    CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
    {
        []() -> CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_RESULT_INTEGRAL_TYPE
        {

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_PREFIX_SYMBOLS  \
    if constexpr (Predicate<Interviewer,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_MIDDLE_SYMBOLS  \
    > :: CONCEPTRODON_NUCLEOLUS_VALUE_RESULT ) \
    { return
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SUFFIX_SYMBOLS  \
    ; }
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SEPARATOR_SYMBOLS   \
    else
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_COUNT   \
    CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep_tail.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_MIDDLE_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_COUNT

            else if constexpr 
            (
                0 <= CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_FUNCTION_NAME
                <Predicate, Interviewer, RestElements ...>
                :: CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
            )
            {
                return CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_LENGTH
                + CONCEPTRODON_TYPELLA_UNCONFORMED_LEFT_INTERVIEW_FUNCTION_NAME
                <Predicate, Interviewer, RestElements ...>
                :: CONCEPTRODON_NUCLEOLUS_VALUE_RESULT ;
            }

            else 
            {
                return -1;
            }
        }()
    };
};
/******************************************************************************************************/
