// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_PARAMETERS_IDENTIFIER
#error "CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_PARAMETERS_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_RESULT_INTEGRAL_TYPE
#error "CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_RESULT_INTEGRAL_TYPE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_LENGTH
#error "CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_LENGTH has not been defined"
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
#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_COUNT
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_COUNT has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_PREFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_PREFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SUFFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SUFFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_MIDDLE_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_MIDDLE_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SEPARATOR_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SEPARATOR_SYMBOLS has already been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template
<

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS   \
    CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    , CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
    ... RestVariables

>
struct CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
<

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    , RestVariables ...

>
{
    static constexpr CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_RESULT_INTEGRAL_TYPE
    CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
    {

        []() -> CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_RESULT_INTEGRAL_TYPE
        {
            
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_PREFIX_SYMBOLS  \
    if constexpr ((...&& CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_PARAMETERS_IDENTIFIER <
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_MIDDLE_SYMBOLS  \
    > :: CONCEPTRODON_NUCLEOLUS_VALUE_RESULT )) \
    { return
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SUFFIX_SYMBOLS  \
    ; }
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SEPARATOR_SYMBOLS   \
    else
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_COUNT   \
    CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep_tail.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_MIDDLE_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_TAIL_COUNT

            else if constexpr 
            (
                0 <= CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE <RestVariables...>
                :: CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
            )
            {
                return CONCEPTRODON_PAGELIS_INDEPENDENT_FIND_LENGTH
                + CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE <RestVariables...>
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