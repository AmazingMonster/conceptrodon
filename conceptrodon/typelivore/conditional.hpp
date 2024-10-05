// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPEBIVORE_CONDITIONAL_H
#define CONCEPTRODON_TYPEBIVORE_CONDITIONAL_H

namespace Conceptrodon {
namespace Typelivore {

template<typename IfTrue, typename IfFalse>
struct Conditional
{
    template<auto>
    struct ProtoPage {};

    template<>
    struct ProtoPage<true>
    { using type = IfTrue; };

    template<>
    struct ProtoPage<false>
    { using type = IfFalse; };




    template<auto...Agreements>
    using Page = ProtoPage<(...&&static_cast<bool>(Agreements))>;

    template<auto...Args>
    using Page_t = ProtoPage<Args...>::type;




    template<typename...Elements>
    using Mold = ProtoPage<(...&&static_cast<bool>(Elements::value))>;

    template<typename...Elements>
    using Mold_t = ProtoPage<(...&&static_cast<bool>(Elements::value))>::type;




    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = ProtoPage<(...&&static_cast<bool>(Predicates<Elements...>::value))>;

        template<typename...Elements>
        using Mold_t = ProtoPage<(...&&static_cast<bool>(Predicates<Elements...>::value))>::type;
    };

    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    



    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = ProtoPage<(...&&static_cast<bool>(Predicates<Variables...>::value))>;
            
        template<auto...Variables>
        using Page_t = ProtoPage<(...&&static_cast<bool>(Predicates<Variables...>::value))>::type;
    };
    
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

}}

#endif