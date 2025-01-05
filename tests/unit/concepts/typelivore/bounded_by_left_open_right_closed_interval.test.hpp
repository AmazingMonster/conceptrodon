// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H

#include "conceptrodon/typelivore/concepts/bounded_by_left_open_right_closed_interval.hpp"
#include "conceptrodon/typelivore/concepts/greater_than.hpp"
#include "conceptrodon/typelivore/concepts/no_greater_than.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestBoundedByClosedInterval {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I>
requires GreaterThan<I, 0>
struct Tester<I>
{ static constexpr int value {1}; };

template<typename I>
requires NoGreaterThan<I, 10>
struct Tester<I>
{ static constexpr int value {2}; };

template<typename I>
requires BoundedByLeftOpenRightClosedInterval<I, 0, 10>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<nullptr>>::value == 0);
static_assert(Tester<Vay<11>>::value == 1);
static_assert(Tester<Vay<0>>::value == 2);
static_assert(Tester<Vay<-1>>::value == 2);
static_assert(Tester<Vay<3>>::value == 3);
static_assert(Tester<Vay<10>>::value == 3);
/******************************************************************************************************/




}}}}

#endif