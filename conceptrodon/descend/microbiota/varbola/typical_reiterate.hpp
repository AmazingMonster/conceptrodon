// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_H
#define CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_H
/******************************************************************************************************/





/******************************************************************************************************/
#include "conceptrodon/sequnivore/paste.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/microbiota/cytoplasm/select_scale.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_proto_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_ALIAS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_ALIAS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_alias_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_TRANSPORT
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_TRANSPORT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_transports/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_FUNCTION_NAME
#error "CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_FUNCTION_NAME   \
    TypicalReiterate
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER   \
    Variables
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_PASTE_FUNCTION
#error "CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_PASTE_FUNCTION has already been defined"
#endif

#define CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_PASTE_FUNCTION   \
    Sequnivore::TypicalPaste
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION
#error "CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION has already been defined"
#endif

#define CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION   \
    Cytoplasm::selectScale
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Varbola {
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
    ... CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_FUNCTION_NAME
{
#include "conceptrodon/descend/microbiota/varbola/typical_reiterate/typical_reiterate.hpp"
};
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_alias_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_transports/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_FUNCTION_NAME
#undef CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER
#undef CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_PASTE_FUNCTION
#undef CONCEPTRODON_VARBOLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
