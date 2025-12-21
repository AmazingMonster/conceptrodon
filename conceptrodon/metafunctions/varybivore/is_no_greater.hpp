// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_NO_GREATER_H
#define CONCEPTRODON_VARYBIVORE_IS_NO_GREATER_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target, auto...Variables>
struct IsNoGreater
{
    static constexpr bool value
    { (...&&(not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsNoGreater_v
{ (...&&(not (Variables < Target))) };

}}

#endif