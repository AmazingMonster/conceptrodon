// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ALL_H
#define CONCEPTRODON_VARYBIVORE_ALL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct All
{
    static constexpr bool value
    { (...&&(static_cast<bool>(Variables))) };
};

template<auto...Variables>
constexpr bool All_v
{ (...&&(static_cast<bool>(Variables))) };

}}

#endif