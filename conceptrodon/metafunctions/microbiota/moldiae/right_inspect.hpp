// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOLDIAE_RIGHT_INSPECT_H
#define CONCEPTRODON_MOLDIAE_RIGHT_INSPECT_H

#include "conceptrodon/utilities/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Moldiae {

template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
{
    template
    <
        template<typename...> class Predicate,
        typename Inspector,
        typename...RestElements
    >
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Inspector,
        RestElements...
    )
    -> std::bool_constant
    <(...&&
        Predicate
        <
            typename RestElements::type,
            typename Inspector::type
        >
        ::value
    )>;
};

}}

#endif