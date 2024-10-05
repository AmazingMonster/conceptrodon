// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_EXPUNGE_H
#define CONCEPTRODON_VARBOLA_EXPUNGE_H

#include "conceptrodon/prefix.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/monotony.hpp"
#include <utility>

namespace Conceptrodon {

namespace Varbola {

template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<Prefix<I>...FrontTargets, Prefix<J>..., typename...BackTargets>
    static consteval auto idyl() -> Shuttle<FrontTargets::value..., BackTargets::value...>;
    
    template<template<auto...> class Operation, Prefix<I>...FrontTargets, Prefix<J>..., typename...BackTargets>
    static consteval auto lark() -> Operation<FrontTargets::value..., BackTargets::value...>;

    template<auto...Variables>
    struct ProtoPage
    { using type = decltype(idyl<Monotony<Variables>...>()); };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = decltype(idyl<Monotony<Variables>...>());
};

}}

#endif