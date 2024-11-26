// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNEQUAL_TO_H
#define CONCEPTRODON_TYPELIVORE_UNEQUAL_TO_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less_than.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, typename RightSide>
concept JustUnequalTo
=   Varybivore::LessThan<LeftSide::value, RightSide::value>
||  Varybivore::LessThan<RightSide::value, LeftSide::value>;

template<typename LeftSide, typename RightSide>
concept UnequalTo
=   Omennivore::Valuable<LeftSide>
&&  Omennivore::Valuable<RightSide>
&&  JustUnequalTo<LeftSide, RightSide>;

}}

#endif