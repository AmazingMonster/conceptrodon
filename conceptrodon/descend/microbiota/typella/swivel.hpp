// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_SWIVEL_H
#define CONCEPTRODON_TYPELLA_SWIVEL_H

#include "utility"
#include "conceptrodon/prefix.hpp"
#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template<Prefix<J>...FrontTargets, typename...BackTargets>
    static constexpr auto idyl() -> Capsule<BackTargets..., FrontTargets...>;

    template<template<typename...> class Operation, Prefix<J>...FrontTargets, typename...BackTargets>
    static constexpr auto lark() -> Operation<BackTargets..., FrontTargets...>;

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