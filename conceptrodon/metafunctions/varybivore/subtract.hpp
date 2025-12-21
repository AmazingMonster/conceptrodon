// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SUBTRACT_H
#define CONCEPTRODON_VARYBIVORE_SUBTRACT_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target, auto...Variables>
struct Subtract
{ 
    static constexpr auto value 
    {(Target -...- Variables)}; 
};

template<auto Target, auto...Variables>
constexpr auto Subtract_v
{(Target -...- Variables)}; 

}}

#endif