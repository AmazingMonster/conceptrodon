// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_LESS_THAN_H
#define CONCEPTRODON_VARYBIVORE_LESS_THAN_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept LessThan = LeftSide < RightSide;

}}

#endif