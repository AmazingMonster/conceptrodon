// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_POP_FUNCTION_NAME
#error "CONCEPTRODON_TYPELLA_TYPICAL_POP_FUNCTION_NAME has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_POP_EXTEND_FRONT_FUNCTION
#error "CONCEPTRODON_TYPELLA_TYPICAL_POP_EXTEND_FRONT_FUNCTION has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_POP_LENGTH
#error "CONCEPTRODON_TYPELLA_TYPICAL_POP_LENGTH has not been defined"
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

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS   \
    CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_TYPELLA_TYPICAL_POP_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    , CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
    PseudoLastElement

    , CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
    ...RestElements

>
struct CONCEPTRODON_TYPELLA_TYPICAL_POP_FUNCTION_NAME
<

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_TYPELLA_TYPICAL_POP_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    , PseudoLastElement
    , RestElements...

>
{
    using CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
    = CONCEPTRODON_TYPELLA_TYPICAL_POP_EXTEND_FRONT_FUNCTION
    <
        typename CONCEPTRODON_TYPELLA_TYPICAL_POP_FUNCTION_NAME <RestElements...>
        :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
    >
    ::template CONCEPTRODON_NUCLEOLUS_MOLD_ALIAS_TEMPLATE
    < 

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_TYPELLA_TYPICAL_POP_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

        , PseudoLastElement
    >;
};
/******************************************************************************************************/
