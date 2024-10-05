// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_STAMP_H
#define CONCEPTRODON_STAMP_H

#include <type_traits>
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {

template<auto Variable, size_t I>
struct Stamp
{ 
    static consteval auto idyl(std::integral_constant<size_t, I>)
    { return Variable; }

    static constexpr size_t lark(Monotony<Variable>)
    { return I; }
};
 
}

#endif