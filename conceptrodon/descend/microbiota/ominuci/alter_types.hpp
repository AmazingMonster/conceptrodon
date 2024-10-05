// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_OMINUCI_ALTER_TYPES_H
#define CONCEPTRODON_OMINUCI_ALTER_TYPES_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/prefix.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/omennivore/extend_front.hpp"
#include <utility>
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_TYPE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_IDYL_FUNCTION
#error "CONCEPTRODON_NUCLEOLUS_IDYL_FUNCTION has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_functions/idyl.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PREFIX_UTILITY
#error "CONCEPTRODON_NUCLEOLUS_PREFIX_UTILITY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_utilities/prefix.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_TRANSPORT
#error "CONCEPTRODON_NUCLEOLUS_MOLD_PARALLEL_TRANSPORT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_transports/mold.hpp"
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
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_ALIAS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_ALIAS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_alias_templates/mold.hpp"
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
#ifdef CONCEPTRODON_OMINUCI_ALTER_TYPES_FUNCTION_NAME
#error "CONCEPTRODON_OMINUCI_ALTER_TYPES_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_OMINUCI_ALTER_TYPES_FUNCTION_NAME   \
    AlterTypes
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_OMINUCI_ALTER_TYPES_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_OMINUCI_ALTER_TYPES_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_OMINUCI_ALTER_TYPES_PARAMETER_IDENTIFIER   \
    IndexSequences
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_OMINUCI_ALTER_TYPES_EXTEND_FRONT_FUNCTION
#error "CONCEPTRODON_OMINUCI_ALTER_TYPES_EXTEND_FRONT_FUNCTION has already been defined"
#endif

#define CONCEPTRODON_OMINUCI_ALTER_TYPES_EXTEND_FRONT_FUNCTION   \
    Omennivore::ExtendFront
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Ominuci {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/descend/microbiota/ominuci/alter_types/alter_types.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_functions/idyl.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_utilities/prefix.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_transports/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/road.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_alias_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_OMINUCI_ALTER_TYPES_FUNCTION_NAME
#undef CONCEPTRODON_OMINUCI_ALTER_TYPES_PARAMETER_IDENTIFIER
#undef CONCEPTRODON_OMINUCI_ALTER_TYPES_EXTEND_FRONT_FUNCTION
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/