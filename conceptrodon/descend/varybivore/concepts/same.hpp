// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SAME_H
#define CONCEPTRODON_VARYBIVORE_SAME_H

#include "conceptrodon/varybivore/is_same.hpp"
#include "conceptrodon/pagelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept Same
=   Pagelivore::Clarify<IsSame, LeftSide, RightSide>
&&  Pagelivore::Clarify<IsSame, RightSide, LeftSide>;

}}

#endif