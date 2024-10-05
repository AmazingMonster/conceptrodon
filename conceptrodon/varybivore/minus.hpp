// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_MINUS_H
#define CONCEPTRODON_VARYBIVORE_MINUS_H

namespace Conceptrodon {
namespace Varybivore {

template<auto I>
struct Minus
{ 
    static constexpr auto value 
    {-I}; 
};

template<auto I>
constexpr auto Minus_v 
{-I};

}}

#endif