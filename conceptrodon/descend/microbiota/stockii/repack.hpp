// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_STOCKII_REPACK_H
#define CONCEPTRODON_STOCKII_REPACK_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/carrier.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER
#error "CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_helpers/detail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_SAIL_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_SAIL_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/sail.hpp"
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
#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PARALLEL_VESSEL
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PARALLEL_VESSEL has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parallel_vessels/rail.hpp"
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
#include "conceptrodon/descend/microbiota/stockii/repack/repack.hpp"
/******************************************************************************************************/

 


/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_helpers/detail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/sail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_uni_templates/sail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/sail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parallel_vessels/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_STOCKII_REPACK_FUNCTION_NAME
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
