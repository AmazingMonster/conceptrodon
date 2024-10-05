// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_BOOLEAN_H
#define CONCEPTRODON_VARYBIVORE_BOOLEAN_H

namespace Conceptrodon {
namespace Varybivore {

template<auto I>
struct Boolean
{
    static constexpr bool value
    { static_cast<bool>(I) };
};

template<auto I>
constexpr bool Boolean_v
{ static_cast<bool>(I) };

}}

#endif