// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ADD_H
#define CONCEPTRODON_VARYBIVORE_ADD_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Init, auto...Variables>
struct Add
{ 
    static constexpr auto value 
    {(Init+...+Variables)}; 
};

template<auto Init, auto...Variables>
constexpr auto Add_v 
{(Init+...+Variables)};

}}

#endif