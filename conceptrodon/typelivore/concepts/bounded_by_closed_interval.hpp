// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_BOUNDED_BY_CLOSED_INTERVAL_H
#define CONCEPTRODON_TYPELIVORE_BOUNDED_BY_CLOSED_INTERVAL_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/no_greater_than.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Element, auto LowerBound, auto UpperBound>
concept JustBoundedByClosedInterval
=   Varybivore::NoGreaterThan<LowerBound, Element::value>
&&  Varybivore::NoGreaterThan<Element::value, UpperBound>;

template<typename Element, auto LowerBound, auto UpperBound>
concept BoundedByClosedInterval
=   Omennivore::Valuable<Element> 
&&  JustBoundedByClosedInterval<Element, LowerBound, UpperBound>;

}}

#endif