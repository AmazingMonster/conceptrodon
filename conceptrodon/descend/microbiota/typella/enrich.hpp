// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_ENRICH_H
#define CONCEPTRODON_TYPELLA_ENRICH_H

#include "conceptrodon/prefix.hpp"
#include "conceptrodon/capsule.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        template<Prefix<I>...FrontTargets, typename...BackTargets>
        static consteval auto idyl() -> Capsule<FrontTargets..., NewElements..., BackTargets...>;

        template<template<typename...> class Operation, Prefix<I>...FrontTargets, typename...BackTargets>
        static consteval auto lark() -> Operation<FrontTargets..., NewElements..., BackTargets...>;
        
        struct Slash
        {
            template<typename...Elements>
            struct ProtoMold
            { using type = decltype(idyl<Elements...>()); };
        };

        template<typename...Elements>
        using Mold = Slash::template ProtoMold<Elements...>;

        template<typename...Elements>
        using Mold_t = decltype(idyl<Elements...>());
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};

}}

#endif