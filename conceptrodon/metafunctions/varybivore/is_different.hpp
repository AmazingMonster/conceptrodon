// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_VARYBIVORE_IS_DIFFERENT_H

#include "conceptrodon/metafunctions/varybivore/solitary_is_different.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Target, auto...Variables>
struct IsDifferent
{
    static constexpr bool value
    {(...&&SolitaryIsDifferent<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsDifferent_v
{(...&&SolitaryIsDifferent<Variables, Target>::value)};

}}

#endif