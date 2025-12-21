// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H
#define CONCEPTRODON_TYPELIVORE_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H

#include "conceptrodon/concepts/omennivore/valuable.hpp"
#include "conceptrodon/concepts/varybivore/no_greater_than.hpp"
#include "conceptrodon/concepts/varybivore/less_than.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Element, auto LowerBound, auto UpperBound>
concept JustBoundedByLeftOpenRightClosedInterval
=   Varybivore::LessThan<LowerBound, Element::value>
&&  Varybivore::NoGreaterThan<Element::value, UpperBound>;

template<typename Element, auto LowerBound, auto UpperBound>
concept BoundedByLeftOpenRightClosedInterval
=   Omennivore::Valuable<Element> 
&&  JustBoundedByLeftOpenRightClosedInterval<Element, LowerBound, UpperBound>;

}}

#endif