// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_EQUAL_H
#define CONCEPTRODON_VARYBIVORE_IS_EQUAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target, auto...Variables>
struct IsEqual
{
    static constexpr bool value
    { (...&&(not (Target < Variables) && not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsEqual_v
{ (...&&(not (Target < Variables) && not (Variables < Target))) };

}}

#endif