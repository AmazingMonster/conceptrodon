// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_FOLD_LEFT_H
#define CONCEPTRODON_MOLDIAE_FOLD_LEFT_H
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER
#error "CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_identifiers/separator.hpp"
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

#include "conceptrodon/microbiota/nucleolus/define_proto_templates/mold.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_synopsis_templates/mold.hpp"
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
#ifdef CONCEPTRODON_MOLDIAE_FOLD_LEFT_FUNCTION_NAME
#error "CONCEPTRODON_MOLDIAE_FOLD_LEFT_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_FOLD_LEFT_FUNCTION_NAME   \
    FoldLeft
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_MOLDIAE_FOLD_LEFT_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_MOLDIAE_FOLD_LEFT_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_FOLD_LEFT_PARAMETER_IDENTIFIER   \
    Operation
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_MOLDIAE_FOLD_LEFT_INITIAL_ELEMENT_IDENTIFIER
#error "CONCEPTRODON_MOLDIAE_FOLD_LEFT_INITIAL_ELEMENT_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_FOLD_LEFT_INITIAL_ELEMENT_IDENTIFIER   \
    FirstElement
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Moldiae {
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_ROAD_PARAMETER_CATEGORY
    CONCEPTRODON_MOLDIAE_FOLD_LEFT_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_MOLDIAE_FOLD_LEFT_FUNCTION_NAME
{
    template
    < 
        CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
        CONCEPTRODON_MOLDIAE_FOLD_LEFT_INITIAL_ELEMENT_IDENTIFIER
    >
    struct CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE
    {
        struct CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER
        {
#include "conceptrodon/microbiota/moldiae/fold_left/fold_left.hpp"
        };

        template
        <
            CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
            ...Agreements
        >
        using CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
        =   CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER 
            ::template CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE <Agreements...>;

        template
        <
            CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
            ...Args
        >
        using CONCEPTRODON_NUCLEOLUS_MOLD_ALIAS_TEMPLATE
        =   CONCEPTRODON_NUCLEOLUS_SEPARATOR_IDENTIFIER 
            ::template CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE <Args...>
            :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT ;
    };

    template
    <
        CONCEPTRODON_NUCLEOLUS_MOLD_PARAMETER_CATEGORY
        ...Agreements
    >
    using CONCEPTRODON_NUCLEOLUS_MOLD_SYNOPSIS_TEMPLATE
    = CONCEPTRODON_NUCLEOLUS_MOLD_PROTO_TEMPLATE <Agreements...>;

};
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_identifiers/separator.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_results/type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_proto_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_synopsis_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_alias_templates/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/mold.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_parameter_categories/road.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_MOLDIAE_FOLD_LEFT_FUNCTION_NAME
#undef CONCEPTRODON_MOLDIAE_FOLD_LEFT_PARAMETER_IDENTIFIER
#undef CONCEPTRODON_MOLDIAE_FOLD_LEFT_INITIAL_ELEMENT_IDENTIFIER
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
