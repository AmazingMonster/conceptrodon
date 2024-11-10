// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ANY_CONDITIONAL_H
#define CONCEPTRODON_VARYBIVORE_ANY_CONDITIONAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto IfTrue, auto IfFalse>
struct AnyConditional
{
    template<auto>
    struct Detail {};

    template<>
    struct Detail<true>
    { static constexpr auto value {IfTrue}; };

    template<>
    struct Detail<false>
    { static constexpr auto value {IfFalse}; };




    template<auto...Agreements>
    using Page = Detail<(...||static_cast<bool>(Agreements))>;

    template<auto...Args>
    static constexpr auto Page_v {Detail<(...||static_cast<bool>(Args))>::value};




    template<typename...Elements>
    using Mold = Detail<(...||static_cast<bool>(Elements::value))>;

    template<typename...Elements>
    static constexpr auto Mold_v { Detail<(...||static_cast<bool>(Elements::value))>::value };




    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        
        template<typename...Elements>
        using Mold = Detail<(...||static_cast<bool>(Predicates<Elements...>::value))>;

        template<typename...Elements>
        static constexpr auto Mold_v 
        { Detail<(...||static_cast<bool>(Predicates<Elements...>::value))>::value };
    };

    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    



    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...||static_cast<bool>(Predicates<Variables...>::value))>;
            
        template<auto...Variables>
        static constexpr auto Page_v 
        { Detail<(...||static_cast<bool>(Predicates<Variables...>::value))>::value };
    };
    
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

}}

#endif