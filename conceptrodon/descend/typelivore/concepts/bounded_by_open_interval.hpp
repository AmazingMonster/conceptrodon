// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_BOUNDED_BY_OPEN_INTERVAL_H
#define CONCEPTRODON_TYPELIVORE_BOUNDED_BY_OPEN_INTERVAL_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Element, typename LowerBound, typename UpperBound>
concept JustBoundedByOpenInterval
=   Varybivore::Less<LowerBound::value, Element::value>
&&  Varybivore::Less<Element::value, UpperBound::value>;

template<typename Element, typename LowerBound, typename UpperBound>
concept BoundedByOpenInterval
=   Omennivore::Valuable<Element> 
&&  Omennivore::Valuable<LowerBound>
&&  Omennivore::Valuable<UpperBound>
&&  JustBoundedByOpenInterval<Element, LowerBound, UpperBound>;

}}

#endif