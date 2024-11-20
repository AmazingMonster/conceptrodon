// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_LESS_H
#define CONCEPTRODON_VARYBIVORE_LESS_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept Less = LeftSide < RightSide;

}}

#endif