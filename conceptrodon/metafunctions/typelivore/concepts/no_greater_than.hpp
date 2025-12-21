// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NO_GREATER_THAN_H
#define CONCEPTRODON_TYPELIVORE_NO_GREATER_THAN_H

#include "conceptrodon/metafunctions/omennivore/concepts/valuable.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/less_than.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/equal_to.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, auto RightSide>
concept JustNoGreaterThan
=   Varybivore::LessThan<LeftSide::value, RightSide>
||  Varybivore::EqualTo<LeftSide::value, RightSide>;

template<typename LeftSide, auto RightSide>
concept NoGreaterThan
=   Omennivore::Valuable<LeftSide>
&&  JustNoGreaterThan<LeftSide, RightSide>;

}}

#endif