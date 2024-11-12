// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_TYPELIVORE_IS_DIFFERENT_H

namespace Conceptrodon {
namespace Typelivore {

template<typename, typename>
struct IsDifferent
{ static constexpr bool value {true}; };

template<typename Element>
struct IsDifferent<Element, Element>
{ static constexpr bool value {false}; };

template<typename LeftSide, typename RightSide>
constexpr bool IsDifferent_v 
{IsDifferent<LeftSide, RightSide>::value};

}}

#endif