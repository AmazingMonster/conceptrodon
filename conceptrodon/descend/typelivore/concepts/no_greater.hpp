// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NO_GREATER_H
#define CONCEPTRODON_TYPELIVORE_NO_GREATER_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less.hpp"
#include "conceptrodon/varybivore/concepts/equal.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, typename RightSide>
concept JustNoGreater 
=   Varybivore::Less<LeftSide::value, RightSide::value>
||  Varybivore::Equal<LeftSide::value, RightSide::value>;

template<typename LeftSide, typename RightSide>
concept NoGreater
=   Omennivore::Valuable<LeftSide>
&&  Omennivore::Valuable<RightSide>
&&  JustNoGreater<LeftSide, RightSide>;

}}

#endif