// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_EQUAL_H
#define CONCEPTRODON_TYPELIVORE_EQUAL_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/equal_to.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, auto RightSide>
concept JustEqualTo = Varybivore::EqualTo<LeftSide::value, RightSide>;

template<typename LeftSide, auto RightSide>
concept EqualTo
=   Omennivore::Valuable<LeftSide>
&&  JustEqualTo<LeftSide, RightSide>;

}}

#endif