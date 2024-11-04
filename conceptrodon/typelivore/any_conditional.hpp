// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPEBIVORE_ANY_CONDITIONAL_H
#define CONCEPTRODON_TYPEBIVORE_ANY_CONDITIONAL_H

namespace Conceptrodon {
namespace Typelivore {

template<typename IfTrue, typename IfFalse>
struct AnyConditional
{
    template<auto>
    struct Detail {};

    template<>
    struct Detail<true>
    { using type = IfTrue; };

    template<>
    struct Detail<false>
    { using type = IfFalse; };




    template<auto...Agreements>
    using Page = Detail<(...||static_cast<bool>(Agreements))>::type;




    template<typename...Elements>
    using Mold = Detail<(...||static_cast<bool>(Elements::value))>::type;




    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Detail<(...||static_cast<bool>(Predicates<Elements...>::value))>::type;
    };

    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    



    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...||static_cast<bool>(Predicates<Variables...>::value))>::type;
    };
    
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

}}

#endif