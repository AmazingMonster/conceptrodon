// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ARE_DISTINCT_H
#define CONCEPTRODON_TYPELIVORE_ARE_DISTINCT_H

#include <cstddef>
#include <utility>
#include "conceptrodon/utilities/label.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    : public Label<Elements*, std::integral_constant<size_t, I>>...
    {
        using Label<Elements*, std::integral_constant<size_t, I>>::lark...;

        template<typename, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        template<typename Element>
        struct Hidden<Element, std::void_t<decltype(lark(std::declval<Element*>()))>>
        { static constexpr bool value {true}; };

        static constexpr bool value {(...&&Hidden<Elements>::value)};
    };

    static constexpr bool value {Detail<std::index_sequence_for<Elements...>>::value};
};

}}

#endif