// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_EQUAL_TO_H
#define CONCEPTRODON_VARYBIVORE_EQUAL_TO_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept EqualTo 
=   not (LeftSide < RightSide)
&&  not (RightSide < LeftSide);

}}

#endif