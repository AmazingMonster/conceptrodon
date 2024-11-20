// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_LESS_H
#define CONCEPTRODON_TYPELIVORE_LESS_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, typename RightSide>
concept JustLess = Varybivore::Less<LeftSide::value, RightSide::value>;

template<typename LeftSide, typename RightSide>
concept Less
=   Omennivore::Valuable<LeftSide>
&&  Omennivore::Valuable<RightSide>
&&  JustLess<LeftSide, RightSide>;

}}

#endif