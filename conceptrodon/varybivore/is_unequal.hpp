// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_UNEQUAL_H
#define CONCEPTRODON_VARYBIVORE_IS_UNEQUAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target, auto...Variables>
struct IsUnequal
{
    static constexpr auto value
    { (...&&(Target < Variables || Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsUnequal_v
{ (...&&(Target < Variables || Variables < Target)) };

}}

#endif