// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ARE_DISTINCT_H
#define CONCEPTRODON_VARYBIVORE_ARE_DISTINCT_H

#include <cstddef>
#include <utility>
#include "conceptrodon/label.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    : public Label<Vay<Variables>, std::integral_constant<size_t, I>>...
    {
        using Label<Vay<Variables>, std::integral_constant<size_t, I>>::lark...;

        template<auto, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        template<auto Variable>
        struct Hidden<Variable, std::void_t<decltype(lark(std::declval<Vay<Variable>>()))>>
        { static constexpr bool value {true}; };

        static constexpr bool value {(...&&Hidden<Variables>::value)};
    };

    static constexpr bool value {Detail<std::make_index_sequence<sizeof...(Variables)>>::value};
};

}}

#endif