// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_CONDITIONAL_H
#define CONCEPTRODON_VARYBIVORE_CONDITIONAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto IfTrue, auto IfFalse>
struct Conditional
{
    template<auto>
    struct ProtoPage {};

    template<>
    struct ProtoPage<true>
    { static constexpr auto value {IfTrue}; };

    template<>
    struct ProtoPage<false>
    { static constexpr auto value {IfFalse}; };




    template<auto...Agreements>
    using Page = ProtoPage<(...&&static_cast<bool>(Agreements))>;

    template<auto...Args>
    static constexpr auto Page_v {ProtoPage<(...&&static_cast<bool>(Args))>::value};




    template<typename...Elements>
    using Mold = ProtoPage<(...&&static_cast<bool>(Elements::value))>;

    template<typename...Elements>
    static constexpr auto Mold_v { ProtoPage<(...&&static_cast<bool>(Elements::value))>::value };




    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        
        template<typename...Elements>
        using Mold = ProtoPage<(...&&static_cast<bool>(Predicates<Elements...>::value))>;

        template<typename...Elements>
        static constexpr auto Mold_v 
        { ProtoPage<(...&&static_cast<bool>(Predicates<Elements...>::value))>::value };
    };

    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    



    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = ProtoPage<(...&&static_cast<bool>(Predicates<Variables...>::value))>;
            
        template<auto...Variables>
        static constexpr auto Page_v 
        { ProtoPage<(...&&static_cast<bool>(Predicates<Variables...>::value))>::value };
    };
    
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

}}

#endif