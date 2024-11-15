// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_H
#define CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/cotanivore/paste.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/microbiota/cytoplasm/select_scale.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/mold.hpp"
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
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_TRANSPORT
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_TRANSPORT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_transports/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_FUNCTION_NAME
#error "CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_FUNCTION_NAME   \
    TypicalReiterate
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER   \
    Elements
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_TYPICAL_PASTE_FUNCTION
#error "CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_TYPICAL_PASTE_FUNCTION has already been defined"
#endif

#define CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_TYPICAL_PASTE_FUNCTION   \
    Cotanivore::TypicalPaste
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION
#error "CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION has already been defined"
#endif

#define CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION   \
    Cytoplasm::selectScale
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Typella {
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
    ... CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_FUNCTION_NAME
{
#include "conceptrodon/descend/microbiota/typella/typical_reiterate/typical_reiterate.hpp"
};
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_alias_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_transports/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_FUNCTION_NAME
#undef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER
#undef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_TYPICAL_PASTE_FUNCTION
#undef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION
/******************************************************************************************************/




/******************************************************************************************************/
#endif 
/******************************************************************************************************/
