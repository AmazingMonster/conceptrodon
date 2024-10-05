// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_SEQUENA_PASTE_H
#define CONCEPTRODON_SEQUENA_PASTE_H
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_CYTOPLASM_FIRST_LLAMA
#error "CONCEPTRODON_CYTOPLASM_FIRST_LLAMA has already been defined"
#endif

#include "conceptrodon/microbiota/cytoplasm/repetition/define_first_llama.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_CYTOPLASM_FIRST_HORSE
#error "CONCEPTRODON_CYTOPLASM_FIRST_HORSE has already been defined"
#endif

#include "conceptrodon/microbiota/cytoplasm/repetition/define_first_horse.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_SEQUENA_PASTE_FUNCTION_NAME
#error "CONCEPTRODON_SEQUENA_PASTE_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_SEQUENA_PASTE_FUNCTION_NAME   \
    Paste
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Sequena {


#include "conceptrodon/microbiota/sequena/paste/paste.hpp"
#include "conceptrodon/microbiota/sequena/paste/paste_standard_integer_sequences.hpp"


}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/cytoplasm/repetition/undef_first_llama.hpp"
#include "conceptrodon/microbiota/cytoplasm/repetition/undef_first_horse.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_SEQUENA_PASTE_FUNCTION_NAME
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
