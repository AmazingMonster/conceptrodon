// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_INCISE_H
#define CONCEPTRODON_VARBOLA_INCISE_H

#include "conceptrodon/prefix.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/monotony.hpp"
#include <utility>

namespace Conceptrodon {
namespace Varbola {

template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<Prefix<I>..., Prefix<J>...Targets, typename...>
    static consteval auto idyl() -> Shuttle<Targets::value...>;

    template<template<auto...> class Operation, Prefix<I>..., Prefix<J>...Targets, typename...>
    static consteval auto lark() -> Operation<Targets::value...>;

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