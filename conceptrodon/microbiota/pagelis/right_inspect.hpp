// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIS_RIGHT_INSPECT_H
#define CONCEPTRODON_PAGELIS_RIGHT_INSPECT_H

#include "conceptrodon/utilities/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Pagelis {

template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
{
    template
    <
        template<auto...> class Predicate,
        typename Inspector,
        typename...RestVays
    >
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Inspector,
        RestVays...
    )
    -> std::bool_constant
    <(...&&
        Predicate
        <
            RestVays::value,
            Inspector::value
        >
        ::value
    )>;
};

}}

#endif