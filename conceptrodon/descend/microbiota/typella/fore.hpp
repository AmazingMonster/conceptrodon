// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_FORE_H
#define CONCEPTRODON_TYPELLA_FORE_H

#include "conceptrodon/prefix.hpp"
#include "conceptrodon/capsule.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<Prefix<I>...Targets, typename...>
    static consteval auto idyl() -> Capsule<Targets...>;

    template<template<typename...> class Operation, Prefix<I>...Targets, typename...>
    static consteval auto lark() -> Operation<Targets...>;

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