// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_PLUS_H
#define CONCEPTRODON_VARYBIVORE_PLUS_H

namespace Conceptrodon {
namespace Varybivore {

template<auto I>
struct Plus
{ 
    static constexpr auto value 
    {+I}; 
};

template<auto I>
constexpr auto Plus_v 
{+I};

}}

#endif