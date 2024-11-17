// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_AMOUNT
#error "CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_AMOUNT has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_CYTOPLASM_ALKANE_LENGTH
#error "CONCEPTRODON_CYTOPLASM_ALKANE_LENGTH has already been defined"
#endif

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
/******************************************************************************************************/




/******************************************************************************************************/
template<>
struct CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
< 
    CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_AMOUNT 
>
{
    using CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
    = CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_VESSEL
    <

#define CONCEPTRODON_CYTOPLASM_ALKANE_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_ALKANE_CARBON_SYMBOLS    \
    CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER ...
#define CONCEPTRODON_CYTOPLASM_ALKANE_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_ALKANE_SEPARATOR_SYMBOLS \
    ,
#define CONCEPTRODON_CYTOPLASM_ALKANE_LENGTH    \
    CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_AMOUNT

#include "conceptrodon/microbiota/cytoplasm/repetition/alkane.hpp"

#undef CONCEPTRODON_CYTOPLASM_ALKANE_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_ALKANE_CARBON_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_ALKANE_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_ALKANE_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_ALKANE_LENGTH

    >;
};
/******************************************************************************************************/
