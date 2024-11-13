// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_H
#define CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/omennivore/extend_back.hpp"
#include "conceptrodon/shuttle.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_ALIAS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_ALIAS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_alias_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_TRANSPORT
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_TRANSPORT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_transports/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_FUNCTION_NAME
#error "CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_FUNCTION_NAME   \
    TypicalTurnOver
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_EXTEND_BACK_FUNCTION
#error "CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_EXTEND_BACK_FUNCTION has already been defined"
#endif

#define CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_EXTEND_BACK_FUNCTION   \
    Omennivore::ExtendBack
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Varbola {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/descend/microbiota/varbola/typical_turn_over/typical_turn_over.hpp"
/******************************************************************************************************/

 


/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_alias_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_transports/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_FUNCTION_NAME
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_VARBOLA_TYPICAL_TURN_OVER_EXTEND_BACK_FUNCTION
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
