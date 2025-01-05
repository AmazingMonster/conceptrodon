// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_TREK_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_MOLDIAE_TREK_PARAMETER_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_TREK_SEND_FUNCTION
#error "CONCEPTRODON_MOLDIAE_TREK_SEND_FUNCTION has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_PARAMETER_CATEGORY
#error "CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
#error "CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_UNI_TEMPLATE
#error "CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_UNI_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_CATEGORY
#error "CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PROTO_TEMPLATE
#error "CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PROTO_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_SYNOPSIS_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_UNI_TEMPLATE
#error "CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_UNI_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_IDENTIFIER has already been defined"
#endif

#define CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_IDENTIFIER    \
    Car
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_CATEGORY
    CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_IDENTIFIER
>
struct CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PROTO_TEMPLATE
{
    struct CONCEPTRODON_NUCLEOLUS_COMMIT_SEPARATOR
    {
        template
        <
            CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_PARAMETER_CATEGORY
            ...Songs
        >
        using CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_SYNOPSIS_TEMPLATE
        = CONCEPTRODON_MOLDIAE_TREK_SEND_FUNCTION
        < CONCEPTRODON_MOLDIAE_TREK_PARAMETER_IDENTIFIER <Songs...> >
        ::template CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_UNI_TEMPLATE
        <
            CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_IDENTIFIER
        >;

        template
        <
            CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            Tavern
        >
        struct CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER
        {
            using CONCEPTRODON_NUCLEOLUS_TYPE_RESULT = Tavern
            < CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_SYNOPSIS_TEMPLATE >; 
        };

        template
        <
            CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            ...Agreements
        >
        using CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_SYNOPSIS_TEMPLATE
        = CONCEPTRODON_NUCLEOLUS_DETAIL_HELPER <Agreements...>
        :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT ;
        
        template
        <
            CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_PARAMETER_CATEGORY
            Tavern
        >
        using CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_TRANSFER_UNI_TEMPLATE
        = Tavern < CONCEPTRODON_MOLDIAE_TREK_COMMITMENT_SYNOPSIS_TEMPLATE >;
    };

#include "conceptrodon/microbiota/moldiae/trek/ascend/ascend/trek.hpp"

};

template
<
    CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_CATEGORY
    ...Agreements
>
using CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_SYNOPSIS_TEMPLATE
= CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PROTO_TEMPLATE <Agreements...>;
/******************************************************************************************************/




/******************************************************************************************************/
#undef CONCEPTRODON_MOLDIAE_TREK_COMPOSITION_PARAMETER_IDENTIFIER
/******************************************************************************************************/
