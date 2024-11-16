// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_LESS_H
#define CONCEPTRODON_VARYBIVORE_LESS_H

#include "conceptrodon/varybivore/is_less.hpp"
#include "conceptrodon/varybivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept Less = Clarify<IsLess, LeftSide, RightSide>;

}}

#endif