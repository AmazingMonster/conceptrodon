// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_SAME_H
#define CONCEPTRODON_VARYBIVORE_IS_SAME_H

namespace Conceptrodon {
namespace Varybivore {

template<auto, auto>
struct IsSame
{ static constexpr bool value {false}; };

template<auto Variable>
struct IsSame<Variable, Variable>
{ static constexpr bool value {true}; };

template<auto LeftSide, auto RightSide>
constexpr auto IsSame_v
{IsSame<LeftSide, RightSide>::value};

}}

#endif