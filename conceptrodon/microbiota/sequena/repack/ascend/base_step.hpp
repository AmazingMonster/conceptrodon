// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_SEQUENA_REPACK_FUNCTION_NAME
#error "CONCEPTRODON_SEQUENA_REPACK_FUNCTION_NAME has not been defined"
#endif

#ifndef CONCEPTRODON_SEQUENA_REPACK_LENGTH
#error "CONCEPTRODON_SEQUENA_REPACK_LENGTH has not been defined"
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
#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_PREFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_PREFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SUFFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SUFFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_MIDDLE_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_MIDDLE_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SEPARATOR_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SEPARATOR_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_COUNT
#error "CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_COUNT has already been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template
<

#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS   \
    CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT    \
    CONCEPTRODON_SEQUENA_REPACK_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_llama.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT

,

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS   \
    CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY ...
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_SEQUENA_REPACK_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

>

struct CONCEPTRODON_SEQUENA_REPACK_FUNCTION_NAME
<

#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_MIDDLE_SYMBOLS   \
    <
#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SUFFIX_SYMBOLS   \
    ...>
#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_COUNT    \
    CONCEPTRODON_SEQUENA_REPACK_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_plain.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_MIDDLE_SYMBOLS 
#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_PLAIN_COUNT

>
{
    template
    <
        CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
        NewPacker
    >
    struct CONCEPTRODON_NUCLEOLUS_RAIL_PROTO_TEMPLATE
    {
        using CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
        = NewPacker
        <

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS   \
    ...
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_SEQUENA_REPACK_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

        >;
    };


    template
    <
        CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
        ... Agreements
    >
    using CONCEPTRODON_NUCLEOLUS_RAIL_SYNOPSIS_TEMPLATE
    = CONCEPTRODON_NUCLEOLUS_RAIL_PROTO_TEMPLATE <Agreements...> ;


    template
    <
        CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
        ... Args
    >
    using CONCEPTRODON_NUCLEOLUS_RAIL_ALIAS_TEMPLATE
    =   CONCEPTRODON_NUCLEOLUS_RAIL_PROTO_TEMPLATE <Args...> 
        :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT ;

    
    template
    <
        CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
        NewPacker
    >
    using CONCEPTRODON_NUCLEOLUS_RAIL_UNI_TEMPLATE
    = NewPacker
    <

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS   \
    ...
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_SEQUENA_REPACK_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    >;

};
/******************************************************************************************************/

