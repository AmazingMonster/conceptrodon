// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_RAILEUS_TRIP_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_RAILEUS_TRIP_PARAMETER_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_PARAMETER_CATEGORY
#error "CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
#error "CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_UNI_TEMPLATE
#error "CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_UNI_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_CATEGORY
#error "CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PROTO_TEMPLATE
#error "CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PROTO_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_MEMBER_ACCESSOR_PREFIX
#error "CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_MEMBER_ACCESSOR_PREFIX has not been defined"
#endif

#ifndef CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_MEMBER_ACCESSOR_SUFFIX
#error "CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_MEMBER_ACCESSOR_SUFFIX has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_IDENTIFIER    \
    Car
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_CATEGORY
    CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PROTO_TEMPLATE
{
    struct CONCEPTRODON_NUCLEOLUS_COMMIT_SEPARATOR
    {
        template
        <
            CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_PARAMETER_CATEGORY
            ...Songs
        >
        using CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE
        = CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_IDENTIFIER
        <
            CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_MEMBER_ACCESSOR_PREFIX
            CONCEPTRODON_RAILEUS_TRIP_PARAMETER_IDENTIFIER
            <Songs...>
            CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_MEMBER_ACCESSOR_SUFFIX
        >;

        template
        <
            CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            Tavern
        >
        struct CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER
        {
            using CONCEPTRODON_NUCLEOLUS_TYPE_RESULT = Tavern
            < CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE >; 
        };

        template
        <
            CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            ...Agreements
        >
        using CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE
        = CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER <Agreements...>
        :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT ;
        
        template
        <
            CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            Tavern
        >
        using CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_TRANSFER_UNI_TEMPLATE
        = Tavern < CONCEPTRODON_RAILEUS_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE >;
    };

#include "conceptrodon/microbiota/raileus/trip/ascend/ascend/trip.hpp"

};

template
<
    CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_CATEGORY
    ...Agreements
>
using CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_SYNOPSIS_TEMPLATE
= CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PROTO_TEMPLATE <Agreements...>;
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_RAILEUS_TRIP_COMPOSITION_PARAMETER_IDENTIFIER
/******************************************************************************************************/
