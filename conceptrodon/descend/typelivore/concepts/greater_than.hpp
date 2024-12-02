// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_GREATER_THAN_H
#define CONCEPTRODON_TYPELIVORE_GREATER_THAN_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less_than.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, auto RightSide>
concept JustGreaterThan = Varybivore::LessThan<RightSide, LeftSide::value>;

template<typename LeftSide, auto RightSide>
concept GreaterThan
=   Omennivore::Valuable<LeftSide>
&&  JustGreaterThan<LeftSide, RightSide>;

}}

#endif