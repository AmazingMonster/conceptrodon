// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_BOUNDED_BY_OPEN_INTERVAL_H
#define CONCEPTRODON_TYPELIVORE_BOUNDED_BY_OPEN_INTERVAL_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/less_than.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Element, auto LowerBound, auto UpperBound>
concept JustBoundedByOpenInterval
=   Varybivore::LessThan<LowerBound, Element::value>
&&  Varybivore::LessThan<Element::value, UpperBound>;

template<typename Element, auto LowerBound, auto UpperBound>
concept BoundedByOpenInterval
=   Omennivore::Valuable<Element> 
&&  JustBoundedByOpenInterval<Element, LowerBound, UpperBound>;

}}

#endif