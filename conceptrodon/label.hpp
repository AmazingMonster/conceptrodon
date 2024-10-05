// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_LABEL_H
#define CONCEPTRODON_LABEL_H

#include <type_traits>

namespace Conceptrodon {

template<typename Element, size_t I>
struct Label
{ 
    static constexpr auto idyl(std::integral_constant<size_t, I>) -> Element;
    static constexpr auto lark(Element) -> std::integral_constant<size_t, I>;
};
 
}

#endif