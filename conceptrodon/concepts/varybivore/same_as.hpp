// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SAME_AS_H
#define CONCEPTRODON_VARYBIVORE_SAME_AS_H

#include "conceptrodon/metafunctions/varybivore/is_same.hpp"
#include "conceptrodon/concepts/pagelivore/passed.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept SameAs
=   Pagelivore::Passed<IsSame, LeftSide, RightSide>
&&  Pagelivore::Passed<IsSame, RightSide, LeftSide>;

}}

#endif