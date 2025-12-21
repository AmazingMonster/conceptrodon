// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_POP_H
#define CONCEPTRODON_TYPELLA_TYPICAL_POP_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/omennivore/extend_front.hpp"
#include "conceptrodon/utilities/capsule.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_synopsis_templates/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_parameter_categories/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_VESSEL
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_VESSEL has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_parallel_vessels/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_TYPELLA_TYPICAL_POP_FUNCTION_NAME
#error "CONCEPTRODON_TYPELLA_TYPICAL_POP_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_TYPELLA_TYPICAL_POP_FUNCTION_NAME   \
    TypicalPop
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_TYPELLA_TYPICAL_POP_EXTEND_FRONT_FUNCTION
#error "CONCEPTRODON_TYPELLA_TYPICAL_POP_EXTEND_FRONT_FUNCTION has already been defined"
#endif

#define CONCEPTRODON_TYPELLA_TYPICAL_POP_EXTEND_FRONT_FUNCTION   \
    Omennivore::ExtendFront
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Typella {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/typella/typical_pop/typical_pop.hpp"
/******************************************************************************************************/

 


/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_synopsis_templates/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_parallel_vessels/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_TYPELLA_TYPICAL_POP_FUNCTION_NAME
#undef CONCEPTRODON_TYPELLA_TYPICAL_POP_EXTEND_FRONT_FUNCTION
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
