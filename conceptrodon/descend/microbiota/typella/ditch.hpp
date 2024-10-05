// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_DITCH_H
#define CONCEPTRODON_TYPELLA_DITCH_H

#include "conceptrodon/prefix.hpp"
#include "conceptrodon/capsule.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template<Prefix<I>...FrontTargets, typename, typename...BackTargets>
    static consteval auto idyl() -> Capsule<FrontTargets..., BackTargets...>;

    template<template<typename...> class Operation, Prefix<I>...FrontTargets, typename, typename...BackTargets>
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