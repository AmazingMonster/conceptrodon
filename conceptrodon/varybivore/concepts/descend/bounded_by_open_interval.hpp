// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_BOUNDED_BY_OPEN_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_BOUNDED_BY_OPEN_INTERVAL_H

#include "conceptrodon/varybivore/concepts/less_than.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Variable, auto LowerBound, auto UpperBound>
concept BoundedByOpenInterval 
=   LessThan<LowerBound, Variable>
&&  LessThan<Variable, UpperBound>;

}}

#endif