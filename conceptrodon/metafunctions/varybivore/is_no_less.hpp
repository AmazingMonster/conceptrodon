// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_NO_LESS_H
#define CONCEPTRODON_VARYBIVORE_IS_NO_LESS_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target, auto...Variables>
struct IsNoLess
{
    static constexpr bool value
    { (...&&(not (Target < Variables))) };
};

template<auto Target, auto...Variables>
constexpr bool IsNoLess_v
{ (...&&(not (Target < Variables))) };

}}

#endif