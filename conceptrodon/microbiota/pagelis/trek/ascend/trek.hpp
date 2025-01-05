// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_TREK_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_PAGELIS_TREK_PARAMETER_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_TREK_SEND_FUNCTION
#error "CONCEPTRODON_PAGELIS_TREK_SEND_FUNCTION has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_TREK_COMMITMENT_PARAMETER_CATEGORY
#error "CONCEPTRODON_PAGELIS_TREK_COMMITMENT_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_PAGELIS_TREK_COMMITMENT_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_PAGELIS_TREK_COMMITMENT_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
#error "CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_UNI_TEMPLATE
#error "CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_UNI_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_CATEGORY
#error "CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PROTO_TEMPLATE
#error "CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PROTO_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_PAGELIS_TREK_COMPOSITION_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_PAGELIS_TREK_COMPOSITION_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_PAGELIS_TREK_COMPOSITION_UNI_TEMPLATE
#error "CONCEPTRODON_PAGELIS_TREK_COMPOSITION_UNI_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_IDENTIFIER    \
    Car
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_CATEGORY
    CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PROTO_TEMPLATE
{
    struct CONCEPTRODON_NUCLEOLUS_COMMIT_SEPARATOR
    {
        template
        <
            CONCEPTRODON_PAGELIS_TREK_COMMITMENT_PARAMETER_CATEGORY
            ...Songs
        >
        using CONCEPTRODON_PAGELIS_TREK_COMMITMENT_SYNOPSIS_TEMPLATE
        = CONCEPTRODON_PAGELIS_TREK_SEND_FUNCTION
        < CONCEPTRODON_PAGELIS_TREK_PARAMETER_IDENTIFIER <Songs...> >
        ::template CONCEPTRODON_PAGELIS_TREK_COMPOSITION_UNI_TEMPLATE
        <
            CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_IDENTIFIER
        >;

        template
        <
            CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            Tavern
        >
        struct CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER
        {
            using CONCEPTRODON_NUCLEOLUS_TYPE_RESULT = Tavern
            < CONCEPTRODON_PAGELIS_TREK_COMMITMENT_SYNOPSIS_TEMPLATE >; 
        };

        template
        <
            CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            ...Agreements
        >
        using CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE
        = CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER <Agreements...>
        :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT ;
        
        template
        <
            CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            Tavern
        >
        using CONCEPTRODON_PAGELIS_TREK_COMMITMENT_TRANSFER_UNI_TEMPLATE
        = Tavern < CONCEPTRODON_PAGELIS_TREK_COMMITMENT_SYNOPSIS_TEMPLATE >;
    };

#include "conceptrodon/microbiota/pagelis/trek/ascend/ascend/trek.hpp"

};

template
<
    CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_CATEGORY
    ...Agreements
>
using CONCEPTRODON_PAGELIS_TREK_COMPOSITION_SYNOPSIS_TEMPLATE
= CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PROTO_TEMPLATE <Agreements...>;
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_PAGELIS_TREK_COMPOSITION_PARAMETER_IDENTIFIER
/******************************************************************************************************/
