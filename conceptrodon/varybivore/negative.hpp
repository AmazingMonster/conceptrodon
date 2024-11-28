// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NEGATIVE_H
#define CONCEPTRODON_VARYBIVORE_NEGATIVE_H

namespace Conceptrodon {
namespace Varybivore {

template<auto I>
struct Negative
{ 
    static constexpr auto value 
    {-I}; 
};

template<auto I>
constexpr auto Negative_v 
{-I};

}}

#endif