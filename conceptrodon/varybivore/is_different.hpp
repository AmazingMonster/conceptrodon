// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_VARYBIVORE_IS_DIFFERENT_H

namespace Conceptrodon {
namespace Varybivore {

template<auto, auto>
struct SolitaryIsDifferent
{ static constexpr bool value {true}; };

template<auto Variable>
struct SolitaryIsDifferent<Variable, Variable>
{ static constexpr bool value {false}; };

template<auto LeftSide, auto RightSide>
constexpr bool SolitaryIsDifferent_v 
{SolitaryIsDifferent<LeftSide, RightSide>::value};

template<auto Target, auto...Variables>
struct IsDifferent
{
    static constexpr bool value
    {(...&&SolitaryIsDifferent<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsDifferent_v
{(...&&SolitaryIsDifferent<Variables, Target>::value)};

}}

#endif