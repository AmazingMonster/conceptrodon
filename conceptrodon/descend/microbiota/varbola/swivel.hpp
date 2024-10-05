// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_SWIVEL_H
#define CONCEPTRODON_VARBOLA_SWIVEL_H

#include "utility"
#include "conceptrodon/prefix.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Varbola {

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template<Prefix<J>...FrontTargets, typename...BackTargets>
    static constexpr auto idyl() -> Shuttle<BackTargets::value..., FrontTargets::value...>;

    template<template<auto...> class Operation, Prefix<J>...FrontTargets, typename...BackTargets>
    static constexpr auto lark() -> Operation<BackTargets::value..., FrontTargets::value...>;

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