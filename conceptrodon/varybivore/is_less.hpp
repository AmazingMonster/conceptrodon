// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_LESS_H
#define CONCEPTRODON_VARYBIVORE_IS_LESS_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target, auto...Variables>
struct IsLess
{
    static constexpr bool value
    { (...&&(Target < Variables)) };
};

template<auto Target, auto...Variables>
constexpr bool IsLess_v
{ (...&&(Target < Variables)) };

}}

#endif