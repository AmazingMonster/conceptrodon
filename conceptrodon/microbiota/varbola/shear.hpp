// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_SHEAR_H
#define CONCEPTRODON_VARBOLA_SHEAR_H

#include "conceptrodon/utilities/prefix.hpp"
#include <utility>

namespace Conceptrodon {

namespace Varbola {

template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{    
    template
    <
        template<auto...> class Operation,
        typename...Targets
    >
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Targets...
    )
    -> Operation<Targets::value...>;
};

}}

#endif