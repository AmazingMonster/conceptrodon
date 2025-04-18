// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NO_LESS_THAN_H
#define CONCEPTRODON_TYPELIVORE_NO_LESS_THAN_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less_than.hpp"
#include "conceptrodon/varybivore/concepts/equal_to.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, auto RightSide>
concept JustNoLessThan
=   Varybivore::LessThan<RightSide, LeftSide::value>
||  Varybivore::EqualTo<LeftSide::value, RightSide>;

template<typename LeftSide, auto RightSide>
concept NoLessThan
=   Omennivore::Valuable<LeftSide>
&&  JustNoLessThan<LeftSide, RightSide>;

}}

#endif