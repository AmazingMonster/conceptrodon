// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_DIFFERENT_FROM_H
#define CONCEPTRODON_VARYBIVORE_DIFFERENT_FROM_H

#include "conceptrodon/varybivore/is_different.hpp"
#include "conceptrodon/pagelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept DifferentFrom
=   Pagelivore::Clarify<IsDifferent, LeftSide, RightSide>
&&  Pagelivore::Clarify<IsDifferent, RightSide, LeftSide>;

}}

#endif