// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_ENRICH_H
#define CONCEPTRODON_VARBOLA_ENRICH_H

#include "conceptrodon/prefix.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/monotony.hpp"
#include <utility>

namespace Conceptrodon {

namespace Varbola {

template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<auto...NewVariables>
    struct ProtoPage
    {
        template<Prefix<I>...FrontTargets, typename...BackTargets>
        static consteval auto idyl() -> Shuttle<FrontTargets::value..., NewVariables..., BackTargets::value...>;

        template<template<auto...> class Operation, Prefix<I>...FrontTargets, typename...BackTargets>
        static consteval auto lark() -> Operation<FrontTargets::value..., NewVariables..., BackTargets::value...>;
        
        struct Slash
        {
            template<auto...Variables>
            struct ProtoPage
            { using type = decltype(idyl<Monotony<Variables>...>()); };
        };

        template<auto...Variables>
        using Page = Slash::template ProtoPage<Variables...>;

        template<auto...Variables>
        using Page_t = decltype(idyl<Monotony<Variables>...>());
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};

}}

#endif