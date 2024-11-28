// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_POSITIVE_H
#define CONCEPTRODON_VARYBIVORE_POSITIVE_H

namespace Conceptrodon {
namespace Varybivore {

template<auto I>
struct Positive
{ 
    static constexpr auto value 
    {+I}; 
};

template<auto I>
constexpr auto Positive_v 
{+I};

}}

#endif