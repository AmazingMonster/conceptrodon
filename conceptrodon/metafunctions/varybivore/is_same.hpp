// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_SAME_H
#define CONCEPTRODON_VARYBIVORE_IS_SAME_H

#include "conceptrodon/metafunctions/varybivore/solitary_is_same.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Target, auto...Variables>
struct IsSame
{
    static constexpr bool value
    {(...&&SolitaryIsSame<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsSame_v
{(...&&SolitaryIsSame<Variables, Target>::value)};

}}

#endif