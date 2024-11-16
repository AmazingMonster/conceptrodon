// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_OMINUCI_REMOVE_TYPES_FUNCTION_NAME
#error "CONCEPTRODON_OMINUCI_REMOVE_TYPES_FUNCTION_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_OMINUCI_REMOVE_TYPES_EXTEND_FRONT_FUNCTION
#error "CONCEPTRODON_OMINUCI_REMOVE_TYPES_EXTEND_FRONT_FUNCTION has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_OMINUCI_REMOVE_TYPES_COUNT
#error "CONCEPTRODON_OMINUCI_REMOVE_TYPES_COUNT has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT
#error "CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT has already been defined"
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
#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_COUNT
#error "CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_COUNT has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_PREFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_PREFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SUFFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SUFFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_MIDDLE_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_MIDDLE_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SEPARATOR_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SEPARATOR_SYMBOLS has already been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template
<

#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS   \
    size_t...
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT    \
    CONCEPTRODON_OMINUCI_REMOVE_TYPES_COUNT

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_llama.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT

    , typename...RestIndexSequences

>
struct CONCEPTRODON_OMINUCI_REMOVE_TYPES_FUNCTION_NAME
<

#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS   \
    std::index_sequence<
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS  \
    ...>
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT    \
    CONCEPTRODON_OMINUCI_REMOVE_TYPES_COUNT

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_llama.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT

    , RestIndexSequences...
>
{
    template
    <

#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_PREFIX_SYMBOLS   \
    CONCEPTRODON_NUCLEOLUS_PREFIX_UTILITY <

#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_MIDDLE_SYMBOLS   \
    >...

#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SUFFIX_SYMBOLS

#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SEPARATOR_SYMBOLS \
    , typename, 

#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_COUNT    \
    CONCEPTRODON_OMINUCI_REMOVE_TYPES_COUNT

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_plain.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_MIDDLE_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_COUNT

        , typename, typename...RestTargets

    >
    static consteval auto CONCEPTRODON_NUCLEOLUS_IDYL_FUNCTION()
    ->  CONCEPTRODON_OMINUCI_REMOVE_TYPES_EXTEND_FRONT_FUNCTION
    <
        decltype
        (
            CONCEPTRODON_OMINUCI_REMOVE_TYPES_FUNCTION_NAME <RestIndexSequences...>
            ::template CONCEPTRODON_NUCLEOLUS_IDYL_FUNCTION <RestTargets...> ()
        )
    >
    ::template CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE 
    < 

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS  \
    ...
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_OMINUCI_REMOVE_TYPES_COUNT

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    >;

    template
    <
        CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
        ...Elements
    >
    using CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE 
    = decltype
    (
        CONCEPTRODON_NUCLEOLUS_IDYL_FUNCTION <Elements...>()
    );
};