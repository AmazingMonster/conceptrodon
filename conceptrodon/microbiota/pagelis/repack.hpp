// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_REPACK_H
#define CONCEPTRODON_PAGELIS_REPACK_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/shuttle.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER
#error "CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_helpers/detail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_VESSEL
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_VESSEL has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parallel_vessels/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_REPACK_FUNCTION_NAME
#error "CONCEPTRODON_PAGELIS_REPACK_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_REPACK_FUNCTION_NAME   \
    Repack
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_REPACK_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_PAGELIS_REPACK_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_REPACK_PARAMETER_IDENTIFIER   \
    NewPacker
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_REPACK_INTEGER_SEQUENCE
#error "CONCEPTRODON_PAGELIS_REPACK_INTEGER_SEQUENCE has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_REPACK_INTEGER_SEQUENCE   \
    std::integer_sequence
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_REPACK_UNIFIED_INTEGER_TYPE
#error "CONCEPTRODON_PAGELIS_REPACK_UNIFIED_INTEGER_TYPE has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_REPACK_UNIFIED_INTEGER_TYPE   \
    std::make_signed_t<size_t>
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Pagelis {
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
    CONCEPTRODON_PAGELIS_REPACK_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_PAGELIS_REPACK_FUNCTION_NAME
{
#include "conceptrodon/microbiota/pagelis/repack/repack.hpp"
#include "conceptrodon/microbiota/pagelis/repack/repack_standard_integer_sequences.hpp"
};
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_helpers/detail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parallel_vessels/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_PAGELIS_REPACK_FUNCTION_NAME
#undef CONCEPTRODON_PAGELIS_REPACK_PARAMETER_IDENTIFIER
#undef CONCEPTRODON_PAGELIS_REPACK_INTEGER_SEQUENCE
#undef CONCEPTRODON_PAGELIS_REPACK_UNIFIED_INTEGER_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
