// Copyright 2026 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_FUNCTORIZE_H
#define CONCEPTRODON_CLXYOSTEON_FUNCTORIZE_H

/******************************************************************************************************/
namespace Conceptrodon {
namespace Clxyosteon {

template<typename Valuable>
struct Functorize
{
    constexpr auto operator()()
    { return Valuable::value; } 
};

}}
/******************************************************************************************************/

#endif