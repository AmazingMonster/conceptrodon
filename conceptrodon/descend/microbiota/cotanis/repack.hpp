// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_COTANIS_REPACK_H
#define CONCEPTRODON_COTANIS_REPACK_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/capsule.hpp"
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
#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_ROAD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_UNI_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_ROAD_UNI_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_uni_templates/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_TRANSPORT
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_TRANSPORT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_transports/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_COTANIS_REPACK_FUNCTION_NAME
#error "CONCEPTRODON_COTANIS_REPACK_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_COTANIS_REPACK_FUNCTION_NAME   \
    Repack
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Cotanis {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/descend/microbiota/cotanis/repack/repack.hpp"
/******************************************************************************************************/

 


/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_helpers/detail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_uni_templates/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_transports/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_COTANIS_REPACK_FUNCTION_NAME
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
