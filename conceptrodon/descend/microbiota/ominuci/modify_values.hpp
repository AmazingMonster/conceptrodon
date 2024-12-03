// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_OMINUCI_MODIFY_VALUES_H
#define CONCEPTRODON_OMINUCI_MODIFY_VALUES_H
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/prefix.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/omennivore/extend_front.hpp"
#include "conceptrodon/vay.hpp"
#include <utility>
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_VALUE_RESULT has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_results/value.hpp"
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

#ifdef CONCEPTRODON_NUCLEOLUS_VAY_UTILITY
#error "CONCEPTRODON_NUCLEOLUS_VAY_UTILITY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_utilities/prefix.hpp"
#include "conceptrodon/microbiota/nucleolus/define_utilities/vay.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_VESSEL
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARALLEL_VESSEL has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parallel_vessels/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_proto_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/define_proto_templates/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_RAIL_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/define_parameter_categories/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_OMINUCI_MODIFY_VALUES_FUNCTION_NAME
#error "CONCEPTRODON_OMINUCI_MODIFY_VALUES_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_OMINUCI_MODIFY_VALUES_FUNCTION_NAME   \
    ModifyValues
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_OMINUCI_MODIFY_VALUES_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_OMINUCI_MODIFY_VALUES_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_OMINUCI_MODIFY_VALUES_PARAMETER_IDENTIFIER   \
    IndexSequences
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_OMINUCI_MODIFY_VALUES_EXTEND_FRONT_FUNCTION
#error "CONCEPTRODON_OMINUCI_MODIFY_VALUES_EXTEND_FRONT_FUNCTION has already been defined"
#endif

#define CONCEPTRODON_OMINUCI_MODIFY_VALUES_EXTEND_FRONT_FUNCTION   \
    Omennivore::ExtendFront
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Ominuci {
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/descend/microbiota/ominuci/modify_values/modify_values.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_results/value.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_functions/idyl.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_utilities/prefix.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_utilities/vay.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parallel_vessels/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/rail.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_OMINUCI_MODIFY_VALUES_FUNCTION_NAME
#undef CONCEPTRODON_OMINUCI_MODIFY_VALUES_PARAMETER_IDENTIFIER
#undef CONCEPTRODON_OMINUCI_MODIFY_VALUES_EXTEND_FRONT_FUNCTION
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/