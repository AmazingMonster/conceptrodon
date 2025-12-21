// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_GREATER_THAN_H
#define CONCEPTRODON_VARYBIVORE_GREATER_THAN_H

#include "conceptrodon/metafunctions/varybivore/concepts/less_than.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept GreaterThan = LessThan<RightSide, LeftSide>;

}}

#endif