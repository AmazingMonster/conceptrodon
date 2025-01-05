// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SAME_AS_H
#define CONCEPTRODON_VARYBIVORE_SAME_AS_H

#include "conceptrodon/varybivore/is_same.hpp"
#include "conceptrodon/pagelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept SameAs
=   Pagelivore::Clarify<IsSame, LeftSide, RightSide>
&&  Pagelivore::Clarify<IsSame, RightSide, LeftSide>;

}}

#endif