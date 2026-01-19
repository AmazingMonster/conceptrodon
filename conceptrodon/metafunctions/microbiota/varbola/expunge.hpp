// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_EXPUNGE_H
#define CONCEPTRODON_VARBOLA_EXPUNGE_H

#include "conceptrodon/utilities/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Varbola {

template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        typename...BackTargets
    >
    static consteval auto idyl
    (
        Prefix<I> auto...front_targets,
        Prefix<J> auto...,
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