// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_SWIVEL_H
#define CONCEPTRODON_TYPELLA_SWIVEL_H

#include "utility"
#include "conceptrodon/prefix.hpp"

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static constexpr auto idyl
    (
        Prefix<J> auto...front_targets,
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