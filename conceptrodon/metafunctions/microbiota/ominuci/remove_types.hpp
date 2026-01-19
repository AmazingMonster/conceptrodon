// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_OMINUCI_REMOVE_TYPES_H
#define CONCEPTRODON_OMINUCI_REMOVE_TYPES_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/utilities/prefix.hpp"
#include "conceptrodon/utilities/tyy.hpp"
#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/metafunctions/omennivore/extend_front.hpp"
#include <utility>
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_IDYL_FUNCTION
#error "CONCEPTRODON_NUCLEOLUS_IDYL_FUNCTION has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_functions/idyl.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PREFIX_UTILITY
#error "CONCEPTRODON_NUCLEOLUS_PREFIX_UTILITY has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_utilities/prefix.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_VESSEL
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_VESSEL has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_parallel_vessels/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_proto_templates/mold.hpp"
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
#ifdef CONCEPTRODON_OMINUCI_REMOVE_TYPES_FUNCTION_NAME
#error "CONCEPTRODON_OMINUCI_REMOVE_TYPES_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_OMINUCI_REMOVE_TYPES_FUNCTION_NAME   \
    RemoveTypes
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_OMINUCI_REMOVE_TYPES_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_OMINUCI_REMOVE_TYPES_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_OMINUCI_REMOVE_TYPES_PARAMETER_IDENTIFIER   \
    IndexSequences
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_OMINUCI_REMOVE_TYPES_EXTEND_FRONT_FUNCTION
#error "CONCEPTRODON_OMINUCI_REMOVE_TYPES_EXTEND_FRONT_FUNCTION has already been defined"
#endif

#define CONCEPTRODON_OMINUCI_REMOVE_TYPES_EXTEND_FRONT_FUNCTION   \
    Omennivore::ExtendFront
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Ominuci {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/ominuci/remove_types/remove_types.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_functions/idyl.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_utilities/prefix.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_parallel_vessels/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_proto_templates/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_synopsis_templates/mold.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_OMINUCI_REMOVE_TYPES_FUNCTION_NAME
#undef CONCEPTRODON_OMINUCI_REMOVE_TYPES_PARAMETER_IDENTIFIER
#undef CONCEPTRODON_OMINUCI_REMOVE_TYPES_EXTEND_FRONT_FUNCTION
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/