// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SOLITARY_IS_SAME_H
#define CONCEPTRODON_VARYBIVORE_SOLITARY_IS_SAME_H

namespace Conceptrodon {
namespace Varybivore {

template<auto, auto>
struct SolitaryIsSame
{ static constexpr bool value {false}; };

template<auto Variable>
struct SolitaryIsSame<Variable, Variable>
{ static constexpr bool value {true}; };

template<auto LeftSide, auto RightSide>
constexpr bool SolitaryIsSame_v
{SolitaryIsSame<LeftSide, RightSide>::value};

}}

#endif