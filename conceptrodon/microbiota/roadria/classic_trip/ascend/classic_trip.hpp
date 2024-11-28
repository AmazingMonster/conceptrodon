// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_PARAMETER_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_PARAMETER_CATEGORY
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_UNI_TEMPLATE
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_UNI_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_CATEGORY
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PROTO_TEMPLATE
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PROTO_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_MEMBER_ACCESSOR_PREFIX
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_MEMBER_ACCESSOR_PREFIX has not been defined"
#endif

#ifndef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_MEMBER_ACCESSOR_SUFFIX
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_MEMBER_ACCESSOR_SUFFIX has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_IDENTIFIER    \
    Car
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_CATEGORY
    CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PROTO_TEMPLATE
{
    struct CONCEPTRODON_NUCLEOLUS_COMMIT_SEPARATOR
    {
        template
        <
            CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_PARAMETER_CATEGORY
            ...Songs
        >
        using CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE
        = CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_IDENTIFIER
        <
            CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_MEMBER_ACCESSOR_PREFIX
            CONCEPTRODON_ROADRIA_CLASSIC_TRIP_PARAMETER_IDENTIFIER
            <Songs...>
            CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_MEMBER_ACCESSOR_SUFFIX
        >;

        template
        <
            CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            Tavern
        >
        struct CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER
        {
            using CONCEPTRODON_NUCLEOLUS_TYPE_RESULT = Tavern
            < CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE >; 
        };

        template
        <
            CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            ...Agreements
        >
        using CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE
        = CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER <Agreements...>
        :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT ;
        
        template
        <
            CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            Tavern
        >
        using CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_TRANSFER_UNI_TEMPLATE
        = Tavern < CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE >;
    };

#include "conceptrodon/microbiota/roadria/classic_trip/ascend/ascend/classic_trip.hpp"

};

template
<
    CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_CATEGORY
    ...Agreements
>
using CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_SYNOPSIS_TEMPLATE
= CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PROTO_TEMPLATE <Agreements...>;
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_ROADRIA_CLASSIC_TRIP_COMPOSITION_PARAMETER_IDENTIFIER
/******************************************************************************************************/
