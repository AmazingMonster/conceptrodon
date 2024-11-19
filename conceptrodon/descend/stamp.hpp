// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_STAMP_H
#define CONCEPTRODON_STAMP_H

#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {

template<auto Variable, typename Key>
struct Stamp
{ 
    static consteval auto idyl(Key) -> Monotony<Variable>;
    static constexpr auto lark(Monotony<Variable>) -> Key;
};
 
}

#endif