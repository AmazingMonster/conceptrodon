// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_H
#define CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_H
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
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/mold.hpp"
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
#ifdef CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_FUNCTION_NAME
#error "CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_FUNCTION_NAME   \
    FoldRightLast
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_PARAMETER_IDENTIFIER   \
    Operation
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Moldiae {
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY
    CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_FUNCTION_NAME
{

#include "conceptrodon/microbiota/moldiae/fold_right_last/fold_right_last.hpp"

};
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_helpers/detail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_FUNCTION_NAME
#undef CONCEPTRODON_MOLDIAE_FOLD_RIGHT_LAST_PARAMETER_IDENTIFIER
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
