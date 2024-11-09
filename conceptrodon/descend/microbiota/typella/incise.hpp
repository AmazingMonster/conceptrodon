// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELLA_INCISE_H
#define CONCEPTRODON_TYPELLA_INCISE_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {

namespace Typella {

template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        Prefix<I>...,
        Prefix<J>...Targets,
        typename...
    >
    static consteval auto idyl() -> Operation<Targets...>;
};

}}

#endif