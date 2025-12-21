// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H

#include "conceptrodon/concepts/varybivore/no_greater_than.hpp"
#include "conceptrodon/concepts/varybivore/less_than.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Variable, auto LowerBound, auto UpperBound>
concept BoundedByLeftOpenRightClosedInterval 
=   LessThan<LowerBound, Variable>
&&  NoGreaterThan<Variable, UpperBound>;

}}

#endif