// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PASTE_FUNCTION
#error "CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PASTE_FUNCTION has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION
#error "CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER
#error "CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PARAMETER_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template<size_t Amount>
struct CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
{
    using CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
    = CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_PASTE_FUNCTION
    <
        typename CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
        <
            CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION (Amount)
        >
        :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
        ,

        typename CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE
        <
            Amount - CONCEPTRODON_TYPELLA_TYPICAL_REITERATE_SELECT_SCALE_FUNCTION (Amount)
        >
        :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT
    >
    :: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT ;
};
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/descend/microbiota/typella/typical_reiterate/ascend/typical_reiterate.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY 
    ... Agreements
>
using CONCEPTRODON_NUCLEOLUS_PAGE_SYNOPSIS_TEMPLATE
= CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE <Agreements...> ;
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_NUCLEOLUS_PAGE_PARAMETER_CATEGORY 
    ... Args
>
using CONCEPTRODON_NUCLEOLUS_PAGE_ALIAS_TEMPLATE
= CONCEPTRODON_NUCLEOLUS_PAGE_PROTO_TEMPLATE <Args...> 
:: CONCEPTRODON_NUCLEOLUS_TYPE_RESULT ;
/******************************************************************************************************/
