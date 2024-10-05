// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_EXPUNGE_H
#define CONCEPTRODON_TYPELLA_EXPUNGE_H

#include "conceptrodon/prefix.hpp"
#include "conceptrodon/capsule.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typella {

template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<Prefix<I>...FrontTargets, Prefix<J>..., typename...BackTargets>
    static consteval auto idyl() -> Capsule<FrontTargets..., BackTargets...>;

    template<template<typename...> class Operation, Prefix<I>...FrontTargets, Prefix<J>..., typename...BackTargets>
    static consteval auto lark() -> Operation<FrontTargets..., BackTargets...>;

    template<typename...Elements>
    struct ProtoMold
    { using type = decltype(idyl<Elements...>()); };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = decltype(idyl<Elements...>());
};

}}

#endif