// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_WARETUS_REPACK_H
#define CONCEPTRODON_WARETUS_REPACK_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/reverie.hpp"
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
#ifdef CONCEPTRODON_NUCLEOLUS_FLOW_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_FLOW_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/flow.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FLOW_UNI_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_FLOW_UNI_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_uni_templates/flow.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_FLOW_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_FLOW_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/road.hpp"
#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/flow.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_PARALLEL_TRANSPORT
#error "CONCEPTRODON_NUCLEOLUS_ROAD_PARALLEL_TRANSPORT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_transports/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_WARETUS_REPACK_FUNCTION_NAME
#error "CONCEPTRODON_WARETUS_REPACK_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_WARETUS_REPACK_FUNCTION_NAME   \
    Repack
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Waretus {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/descend/microbiota/waretus/repack/repack.hpp"
/******************************************************************************************************/

 


/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_helpers/detail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/flow.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_uni_templates/flow.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/flow.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_transports/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_WARETUS_REPACK_FUNCTION_NAME
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
