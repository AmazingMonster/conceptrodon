// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_SWIVEL_H
#define CONCEPTRODON_TYPELLA_SWIVEL_H

#include "utility"
#include "conceptrodon/utilities/prefix.hpp"

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Swivel {};

template<size_t...I>
struct Swivel<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static constexpr auto idyl
    (
        Prefix<I> auto...front_targets,
        BackTargets...
    )
    -> Operation
    <
        typename BackTargets::type...,
        typename decltype(front_targets)::type...
    >;
};

}}

#endif