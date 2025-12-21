// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_GREATER_H
#define CONCEPTRODON_VARYBIVORE_IS_GREATER_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target, auto...Variables>
struct IsGreater
{
    static constexpr bool value
    { (...&&(Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsGreater_v
{ (...&&(Variables < Target)) };

}}

#endif