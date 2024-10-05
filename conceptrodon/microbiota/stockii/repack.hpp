// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_STOCKII_REPACK_H
#define CONCEPTRODON_STOCKII_REPACK_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/phantom.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_SAIL_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_SAIL_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_proto_templates/sail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_SAIL_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_SAIL_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/sail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_SAIL_ALIAS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_SAIL_ALIAS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_alias_templates/sail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_SAIL_UNI_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_SAIL_UNI_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_uni_templates/sail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_SAIL_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_SAIL_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/sail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PARALLEL_TRANSPORT
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PARALLEL_TRANSPORT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_transports/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_STOCKII_REPACK_FUNCTION_NAME
#error "CONCEPTRODON_STOCKII_REPACK_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_STOCKII_REPACK_FUNCTION_NAME   \
    Repack
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Stockii {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/stockii/repack/repack.hpp"
/******************************************************************************************************/

 


/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/sail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/sail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_alias_templates/sail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_uni_templates/sail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/sail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_transports/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_STOCKII_REPACK_FUNCTION_NAME
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
