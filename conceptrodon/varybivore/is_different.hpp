// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_VARYBIVORE_IS_DIFFERENT_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
struct IsDifferent
{ static constexpr bool value {true}; };

template<auto Variable>
struct IsDifferent<Variable, Variable>
{ static constexpr bool value {false}; };

template<auto LeftSide, auto RightSide>
constexpr auto IsDifferent_v 
{IsDifferent<LeftSide, RightSide>::value};

}}

#endif