// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_DIFFERENT_H
#define CONCEPTRODON_VARYBIVORE_DIFFERENT_H

#include "conceptrodon/varybivore/is_different.hpp"
#include "conceptrodon/varybivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept Different
=   Clarify<IsDifferent, LeftSide, RightSide>
&&  Clarify<IsDifferent, RightSide, LeftSide>;

}}

#endif