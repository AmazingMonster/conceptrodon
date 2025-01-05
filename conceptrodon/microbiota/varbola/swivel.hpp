// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_SWIVEL_H
#define CONCEPTRODON_VARBOLA_SWIVEL_H

#include "utility"
#include "conceptrodon/prefix.hpp"

namespace Conceptrodon {
namespace Varbola {

template<typename>
struct Swivel {};

template<size_t...I>
struct Swivel<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackTargets
    >
    static constexpr auto idyl(Prefix<I> auto...front_targets, BackTargets...)
    -> Operation
    <
        BackTargets::value...,
        decltype(front_targets)::value...
    >;
};

}}

#endif