// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_SEQUENA_PASTE_LENGTH
#error "CONCEPTRODON_SEQUENA_PASTE_LENGTH has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_CYTOPLASM_MICRO_HORSE_PREFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_HORSE_PREFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_HORSE_SUFFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_HORSE_SUFFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_HORSE_SEPARATOR_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_HORSE_SEPARATOR_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_HORSE_COUNT
#error "CONCEPTRODON_CYTOPLASM_MICRO_HORSE_COUNT has already been defined"
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
#ifdef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_PREFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_WORLD_PREFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SUFFIX_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SUFFIX_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SECOND_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SECOND_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_HINDER_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_HINDER_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SEPARATOR_SYMBOLS
#error "CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SEPARATOR_SYMBOLS has already been defined"
#endif

#ifdef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_COUNT
#error "CONCEPTRODON_CYTOPLASM_MICRO_WORLD_COUNT has already been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template
<

#define CONCEPTRODON_CYTOPLASM_MICRO_HORSE_PREFIX_SYMBOLS   \
    template<typename, auto...> class
#define CONCEPTRODON_CYTOPLASM_MICRO_HORSE_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_HORSE_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_HORSE_COUNT    \
    CONCEPTRODON_SEQUENA_PASTE_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_horse.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_HORSE_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_HORSE_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_HORSE_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_HORSE_COUNT

,

#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS   \
    typename
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT    \
    CONCEPTRODON_SEQUENA_PASTE_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_llama.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_LLAMA_COUNT

,

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS   \
    auto...
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_SEQUENA_PASTE_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

    , typename...RestPacks
>

struct CONCEPTRODON_SEQUENA_PASTE_FUNCTION_NAME
<

#define CONCEPTRODON_CYTOPLASM_MICRO_WORLD_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SECOND_SYMBOLS   \
    <
#define CONCEPTRODON_CYTOPLASM_MICRO_WORLD_HINDER_SYMBOLS   \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SUFFIX_SYMBOLS   \
    ...>
#define CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_WORLD_COUNT    \
    CONCEPTRODON_SEQUENA_PASTE_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_world.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SECOND_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_HINDER_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_WORLD_COUNT

    , RestPacks...
>
{
    using CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
    =  CONCEPTRODON_SEQUENA_PASTE_FUNCTION_NAME
    <
        CONCEPTRODON_CYTOPLASM_FIRST_HORSE
        <
            CONCEPTRODON_CYTOPLASM_FIRST_LLAMA
    
            ,

#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS   \
    ...
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS    \
    ,
#define CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT    \
    CONCEPTRODON_SEQUENA_PASTE_LENGTH

#include "conceptrodon/microbiota/cytoplasm/repetition/micro_sheep.hpp"

#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_PREFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SUFFIX_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_SEPARATOR_SYMBOLS
#undef CONCEPTRODON_CYTOPLASM_MICRO_SHEEP_COUNT

        >
        , RestPacks...
    >:: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT ;
};
/******************************************************************************************************/

