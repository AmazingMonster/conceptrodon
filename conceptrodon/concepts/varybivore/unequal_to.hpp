// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNEQUAL_TO_H
#define CONCEPTRODON_VARYBIVORE_UNEQUAL_TO_H

#include "conceptrodon/concepts/varybivore/less_than.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept UnequalTo
=   LessThan<LeftSide, RightSide>
||  LessThan<RightSide, LeftSide>;

}}

#endif