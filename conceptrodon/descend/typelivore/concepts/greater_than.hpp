// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_GREATER_THAN_H
#define CONCEPTRODON_TYPELIVORE_GREATER_THAN_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less_than.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, typename RightSide>
concept JustGreaterThan = Varybivore::LessThan<RightSide::value, LeftSide::value>;

template<typename LeftSide, typename RightSide>
concept Greater
=   Omennivore::Valuable<LeftSide>
&&  Omennivore::Valuable<RightSide>
&&  JustGreaterThan<LeftSide, RightSide>;

}}

#endif