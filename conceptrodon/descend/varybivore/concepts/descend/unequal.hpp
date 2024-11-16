// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNEQUAL_H
#define CONCEPTRODON_VARYBIVORE_UNEQUAL_H

#include "conceptrodon/descend/varybivore/concepts/less.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept Unequal
=   Less<LeftSide, RightSide>
||  Less<RightSide, LeftSide>;

}}

#endif