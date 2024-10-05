// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_SEQUENA_REPACK_H
#define CONCEPTRODON_SEQUENA_REPACK_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/shuttle.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_proto_templates/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_RAIL_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_ALIAS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_RAIL_ALIAS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_alias_templates/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_UNI_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_RAIL_UNI_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_uni_templates/rail.hpp"
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
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_TRANSPORT
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_TRANSPORT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_transports/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_SEQUENA_REPACK_FUNCTION_NAME
#error "CONCEPTRODON_SEQUENA_REPACK_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_SEQUENA_REPACK_FUNCTION_NAME   \
    Repack
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_SEQUENA_REPACK_INTEGER_SEQUENCE
#error "CONCEPTRODON_SEQUENA_REPACK_INTEGER_SEQUENCE has already been defined"
#endif

#define CONCEPTRODON_SEQUENA_REPACK_INTEGER_SEQUENCE   \
    std::integer_sequence
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_SEQUENA_REPACK_UNIFIED_INTEGER_TYPE
#error "CONCEPTRODON_SEQUENA_REPACK_UNIFIED_INTEGER_TYPE has already been defined"
#endif

#define CONCEPTRODON_SEQUENA_REPACK_UNIFIED_INTEGER_TYPE   \
    std::make_signed_t<size_t>
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Sequena {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/sequena/repack/repack.hpp"
#include "conceptrodon/microbiota/sequena/repack/repack_standard_integer_sequences.hpp"
/******************************************************************************************************/

 


/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_alias_templates/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_uni_templates/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_transports/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_SEQUENA_REPACK_FUNCTION_NAME
#undef CONCEPTRODON_SEQUENA_REPACK_INTEGER_SEQUENCE
#undef CONCEPTRODON_SEQUENA_REPACK_UNIFIED_INTEGER_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
