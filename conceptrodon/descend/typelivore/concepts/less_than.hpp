// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_LESS_THAN_H
#define CONCEPTRODON_TYPELIVORE_LESS_THAN_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less_than.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, typename RightSide>
concept JustLessThan = Varybivore::LessThan<LeftSide::value, RightSide::value>;

template<typename LeftSide, typename RightSide>
concept LessThan
=   Omennivore::Valuable<LeftSide>
&&  Omennivore::Valuable<RightSide>
&&  JustLessThan<LeftSide, RightSide>;

}}

#endif