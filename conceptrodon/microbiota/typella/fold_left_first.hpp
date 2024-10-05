// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_FOLD_LEFT_FIRST_H
#define CONCEPTRODON_TYPELLA_FOLD_LEFT_FIRST_H
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_ROAD_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_proto_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/define_proto_templates/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_ROAD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_ROAD_ALIAS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_ROAD_ALIAS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_alias_templates/road.hpp"
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
#ifdef CONCEPTRODON_TYPELLA_FOLD_LEFT_FIRST_FUNCTION_NAME
#error "CONCEPTRODON_TYPELLA_FOLD_LEFT_FIRST_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_TYPELLA_FOLD_LEFT_FIRST_FUNCTION_NAME   \
    FoldLeftFirst
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Typella {


#include "conceptrodon/microbiota/typella/fold_left_first/fold_left_first.hpp"


}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_alias_templates/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_uni_templates/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_TYPELLA_FOLD_LEFT_FIRST_FUNCTION_NAME
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
