// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_FOLD_LEFT_H
#define CONCEPTRODON_PAGELIS_FOLD_LEFT_H
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_SLASH_SEPARATOR
#error "CONCEPTRODON_NUCLEOLUS_SLASH_SEPARATOR has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_separators/slash.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VALUE_RESULT
#error "CONCEPTRODON_NUCLEOLUS_VALUE_RESULT has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_results/value.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_proto_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_synopsis_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_VARIABLE_TEMPLATE
#error "CONCEPTRODON_NUCLEOLUS_PAGE_VARIABLE_TEMPLATE has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_variable_templates/page.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY has already been defined"
#endif

#ifdef CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
#error "CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_parameter_categories/page.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/define_parameter_categories/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_FOLD_LEFT_FUNCTION_NAME
#error "CONCEPTRODON_PAGELIS_FOLD_LEFT_FUNCTION_NAME has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_FOLD_LEFT_FUNCTION_NAME   \
    FoldLeft
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_FOLD_LEFT_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_PAGELIS_FOLD_LEFT_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_FOLD_LEFT_PARAMETER_IDENTIFIER   \
    Operation
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_FOLD_LEFT_INITIAL_VARIABLE_IDENTIFIER
#error "CONCEPTRODON_PAGELIS_FOLD_LEFT_INITIAL_VARIABLE_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_FOLD_LEFT_INITIAL_VARIABLE_IDENTIFIER   \
    FirstVariable
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Pagelis {
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_RAIL_PARAMETER_CATEGORY
    CONCEPTRODON_PAGELIS_FOLD_LEFT_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_PAGELIS_FOLD_LEFT_FUNCTION_NAME
{
    template
    < 
        CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
        CONCEPTRODON_PAGELIS_FOLD_LEFT_INITIAL_VARIABLE_IDENTIFIER
    >
    struct CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
    {
        struct CONCEPTRODON_NUCLEOLUS_SLASH_SEPARATOR
        {
#include "conceptrodon/metafunctions/microbiota/pagelis/fold_left/fold_left.hpp"
        };

        template
        <
            CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
            ...Agreements
        >
        using CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE
        =   CONCEPTRODON_NUCLEOLUS_SLASH_SEPARATOR 
            ::template CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE <Agreements...>;

        template
        <
            CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
            ...Args
        >
        static constexpr auto CONCEPTRODON_NUCLEOLUS_PAGE_VARIABLE_TEMPLATE
        =   CONCEPTRODON_NUCLEOLUS_SLASH_SEPARATOR 
            ::template CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE <Args...>
            :: CONCEPTRODON_NUCLEOLUS_VALUE_RESULT;
    };

    template
    <
        CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY
        ...Agreements
    >
    using CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE
    = CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE <Agreements...>;

};
/******************************************************************************************************/




/******************************************************************************************************/
}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_separators/slash.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_results/value.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_proto_templates/page.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_synopsis_templates/page.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_variable_templates/page.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_parameter_categories/page.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_parameter_categories/rail.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_PAGELIS_FOLD_LEFT_FUNCTION_NAME
#undef CONCEPTRODON_PAGELIS_FOLD_LEFT_PARAMETER_IDENTIFIER
#undef CONCEPTRODON_PAGELIS_FOLD_LEFT_INITIAL_VARIABLE_IDENTIFIER
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
