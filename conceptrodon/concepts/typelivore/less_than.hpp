// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_LESS_THAN_H
#define CONCEPTRODON_TYPELIVORE_LESS_THAN_H

#include "conceptrodon/concepts/omennivore/valuable.hpp"
#include "conceptrodon/concepts/varybivore/less_than.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, auto RightSide>
concept JustLessThan = Varybivore::LessThan<LeftSide::value, RightSide>;

template<typename LeftSide, auto RightSide>
concept LessThan
=   Omennivore::Valuable<LeftSide>
&&  JustLessThan<LeftSide, RightSide>;

}}

#endif