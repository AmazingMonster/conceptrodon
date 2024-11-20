// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H

#include "conceptrodon/varybivore/concepts/descend/no_greater.hpp"
#include "conceptrodon/varybivore/concepts/less.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Variable, auto LowerBound, auto UpperBound>
concept BoundedByLeftClosedRightOpenInterval
=   NoGreater<LowerBound, Variable>
&&  Less<Variable, UpperBound>;

}}

#endif