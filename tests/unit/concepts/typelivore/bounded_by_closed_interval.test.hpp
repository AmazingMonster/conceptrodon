// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_BOUNDED_BY_CLOSED_INTERVAL_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_BOUNDED_BY_CLOSED_INTERVAL_H

#include "conceptrodon/descend/typelivore/concepts/bounded_by_closed_interval.hpp"
#include "conceptrodon/descend/typelivore/concepts/no_less_than.hpp"
#include "conceptrodon/descend/typelivore/concepts/no_greater_than.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestBoundedByClosedInterval {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I>
requires NoLessThan<I, 0>
struct Tester<I>
{ static constexpr int value {1}; };

template<typename I>
requires NoGreaterThan<I, 10>
struct Tester<I>
{ static constexpr int value {2}; };

template<typename I>
requires BoundedByClosedInterval<I, 0, 10>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<nullptr>>::value == 0);
static_assert(Tester<Monotony<11>>::value == 1);
static_assert(Tester<Monotony<-1>>::value == 2);
static_assert(Tester<Monotony<10>>::value == 3);
static_assert(Tester<Monotony<3>>::value == 3);
static_assert(Tester<Monotony<0>>::value == 3);
/******************************************************************************************************/




}}}}

#endif