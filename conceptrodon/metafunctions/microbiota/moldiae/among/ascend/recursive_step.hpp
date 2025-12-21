// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_AMONG_FUNCTION_NAME
#error "CONCEPTRODON_MOLDIAE_AMONG_FUNCTION_NAME has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_AMONG_AMOUNT
#error "CONCEPTRODON_MOLDIAE_AMONG_AMOUNT has not been defined"
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
#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_COUNT
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_COUNT has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_PREFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_PREFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_SUFFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_SUFFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_MIDDLE_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_MIDDLE_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_SEPARATOR_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_SEPARATOR_SYMBOLS has already been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template
<

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS   \
    CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_MOLDIAE_AMONG_AMOUNT

#include "conceptrodon/metafunctions/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    , CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY
    ... RestContainers

>
struct CONCEPTRODON_MOLDIAE_AMONG_FUNCTION_NAME
<

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_MOLDIAE_AMONG_AMOUNT

#include "conceptrodon/metafunctions/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    , RestContainers...

>
{
    template<size_t I>
    struct CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
    {
        template
        <
            CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
            ...Agreements
        >
        using CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
        = CONCEPTRODON_MOLDIAE_AMONG_FUNCTION_NAME <RestContainers...>
        ::template CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE < I - CONCEPTRODON_MOLDIAE_AMONG_AMOUNT > 
        ::template CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE <Agreements...> ;
    };

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_PREFIX_SYMBOLS  \
    template<>  \
    struct CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE <
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_MIDDLE_SYMBOLS  \
    >   \
    { \
        template    \
        <   \
            CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY  \
            ... Agreements\
        >   \
        using CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE =
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_SUFFIX_SYMBOLS  \
        <Agreements...> ;   \
    }
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_SEPARATOR_SYMBOLS   \
    ;
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_COUNT   \
    CONCEPTRODON_MOLDIAE_AMONG_AMOUNT

#include "conceptrodon/metafunctions/microbiota/cytoplasm/repetition/micro_sheep_horn.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_MIDDLE_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_HORN_COUNT

    ;

    template
    <
        CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
        ...Agreements 
    >
    using CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE
    =   CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE <Agreements...>;
    
};
/******************************************************************************************************/
