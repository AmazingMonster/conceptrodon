// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_BOUNDED_BY_CLOSED_INTERVAL_H
#define CONCEPTRODON_TYPELIVORE_BOUNDED_BY_CLOSED_INTERVAL_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/descend/no_greater.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Element, typename LowerBound, typename UpperBound>
concept JustBoundedByClosedInterval
=   Varybivore::NoGreater<LowerBound::value, Element::value>
&&  Varybivore::NoGreater<Element::value, UpperBound::value>;

template<typename Element, typename LowerBound, typename UpperBound>
concept BoundedByClosedInterval
=   Omennivore::Valuable<Element> 
&&  Omennivore::Valuable<LowerBound>
&&  Omennivore::Valuable<UpperBound>
&&  JustBoundedByClosedInterval<Element, LowerBound, UpperBound>;

}}

#endif