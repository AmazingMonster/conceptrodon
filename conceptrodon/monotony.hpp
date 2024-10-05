// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MONOTONY_H
#define CONCEPTRODON_MONOTONY_H

namespace Conceptrodon {
    
template<auto Variable>
struct Monotony
{ static constexpr auto value {Variable}; };
 
}

#endif