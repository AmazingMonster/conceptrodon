// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H
#define CONCEPTRODON_TYPELIVORE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H

#include "conceptrodon/concepts/omennivore/valuable.hpp"
#include "conceptrodon/concepts/varybivore/no_greater_than.hpp"
#include "conceptrodon/concepts/varybivore/less_than.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Element, auto LowerBound, auto UpperBound>
concept JustBoundedByLeftClosedRightOpenInterval
=   Varybivore::NoGreaterThan<LowerBound, Element::value>
&&  Varybivore::LessThan<Element::value, UpperBound>;

template<typename Element, auto LowerBound, auto UpperBound>
concept BoundedByLeftClosedRightOpenInterval
=   Omennivore::Valuable<Element> 
&&  JustBoundedByLeftClosedRightOpenInterval<Element, LowerBound, UpperBound>;

}}

#endif