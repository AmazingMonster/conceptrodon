// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_FOLD_LEFT_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_PAGELIS_FOLD_LEFT_PARAMETER_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_FOLD_LEFT_AMOUNT
#error "CONCEPTRODON_PAGELIS_FOLD_LEFT_AMOUNT has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_FOLD_LEFT_INITIAL_VARIABLE_IDENTIFIER
#error "CONCEPTRODON_PAGELIS_FOLD_LEFT_INITIAL_VARIABLE_IDENTIFIER has not been defined"
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
#ifdef CONCEPTRODON_CYTOPLASM_ALKANE_PREFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_ALKANE_PREFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_ALKANE_CARBON_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_ALKANE_CARBON_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_ALKANE_SUFFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_ALKANE_SUFFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_ALKANE_SEPARATOR_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_ALKANE_SEPARATOR_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_ALKANE_LENGTH
#error "CONCEPTRODON_CYTOPLASM_ALKANE_LENGTH has already been defined"
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
    CONCEPTRODON_PAGELIS_FOLD_LEFT_AMOUNT
#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

>
struct CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
<

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_PAGELIS_FOLD_LEFT_AMOUNT
#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

>
{
    static constexpr auto CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
    = 
#define CONCEPTRODON_CYTOPLASM_ALKANE_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_ALKANE_CARBON_SYMBOLS    \
    CONCEPTRODON_PAGELIS_FOLD_LEFT_PARAMETER_IDENTIFIER
#define CONCEPTRODON_CYTOPLASM_ALKANE_SUFFIX_SYMBOLS    \
    <
#define CONCEPTRODON_CYTOPLASM_ALKANE_SEPARATOR_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_ALKANE_LENGTH    \
    CONCEPTRODON_PAGELIS_FOLD_LEFT_AMOUNT
#include "conceptrodon/microbiota/cytoplasm/repetition/alkane.hpp"
#undef CONCEPTRODON_CYTOPLASM_ALKANE_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_ALKANE_CARBON_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_ALKANE_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_ALKANE_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_ALKANE_LENGTH

        CONCEPTRODON_PAGELIS_FOLD_LEFT_INITIAL_VARIABLE_IDENTIFIER ,

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS   \
    >:: CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_PAGELIS_FOLD_LEFT_AMOUNT
#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    ;
};

/******************************************************************************************************/
