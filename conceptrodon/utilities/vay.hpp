// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VAY_H
#define CONCEPTRODON_VAY_H

namespace Conceptrodon {
    
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
 
}

#endif