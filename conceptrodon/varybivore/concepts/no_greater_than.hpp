// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NO_GREATER_THAN_H
#define CONCEPTRODON_VARYBIVORE_NO_GREATER_THAN_H

#include "conceptrodon/varybivore/concepts/less_than.hpp"
#include "conceptrodon/varybivore/concepts/equal_to.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept NoGreaterThan
=   LessThan<LeftSide, RightSide>
||  EqualTo<LeftSide, RightSide>;

}}

#endif