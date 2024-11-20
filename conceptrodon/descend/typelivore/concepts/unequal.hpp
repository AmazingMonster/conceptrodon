// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNEQUAL_H
#define CONCEPTRODON_TYPELIVORE_UNEQUAL_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, typename RightSide>
concept JustUnequal
=   Varybivore::Less<LeftSide::value, RightSide::value>
||  Varybivore::Less<RightSide::value, LeftSide::value>;

template<typename LeftSide, typename RightSide>
concept Unequal
=   Omennivore::Valuable<LeftSide>
&&  Omennivore::Valuable<RightSide>
&&  JustUnequal<LeftSide, RightSide>;

}}

#endif