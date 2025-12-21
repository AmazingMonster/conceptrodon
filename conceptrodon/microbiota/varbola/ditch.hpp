// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_DITCH_H
#define CONCEPTRODON_VARBOLA_DITCH_H

#include "conceptrodon/utilities/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Varbola {

template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackTargets
    >
    static consteval auto idyl
    (
        Prefix<I> auto...front_targets,
        auto,
        BackTargets...
    )
    -> Operation
    <
        decltype(front_targets)::value...,
        BackTargets::value...
    >;
};

}}

#endif