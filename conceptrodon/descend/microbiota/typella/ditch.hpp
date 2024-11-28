// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_DITCH_H
#define CONCEPTRODON_TYPELLA_DITCH_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        Prefix<I>...FrontTargets,
        typename,
        typename...BackTargets
    >
    static consteval auto idyl() -> Operation<FrontTargets..., BackTargets...>;
};

}}

#endif