// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H
#define CONCEPTRODON_TYPELIVORE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/descend/no_greater.hpp"
#include "conceptrodon/varybivore/concepts/less.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Element, typename LowerBound, typename UpperBound>
concept JustBoundedByLeftClosedRightOpenInterval
=   Varybivore::NoGreater<LowerBound::value, Element::value>
&&  Varybivore::Less<Element::value, UpperBound::value>;

template<typename Element, typename LowerBound, typename UpperBound>
concept BoundedByLeftClosedRightOpenInterval
=   Omennivore::Valuable<Element> 
&&  Omennivore::Valuable<LowerBound>
&&  Omennivore::Valuable<UpperBound>
&&  JustBoundedByLeftClosedRightOpenInterval<Element, LowerBound, UpperBound>;

}}

#endif