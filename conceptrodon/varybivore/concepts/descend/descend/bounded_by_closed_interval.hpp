// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_BOUNDED_BY_CLOSED_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_BOUNDED_BY_CLOSED_INTERVAL_H

#include "conceptrodon/varybivore/concepts/descend/no_greater.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Variable, auto LowerBound, auto UpperBound>
concept BoundedByClosedInterval 
=   NoGreater<LowerBound, Variable>
&&  NoGreater<Variable, UpperBound>;

}}

#endif