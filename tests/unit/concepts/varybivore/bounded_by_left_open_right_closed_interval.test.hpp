// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H

#include "conceptrodon/concepts/varybivore/bounded_by_left_open_right_closed_interval.hpp"
#include "conceptrodon/concepts/varybivore/greater_than.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestBoundedByClosedInterval {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto I>
requires GreaterThan<I, 0>
struct Tester<I>
{ static constexpr int value {1}; };

template<auto I>
requires NoGreaterThan<I, 10>
struct Tester<I>
{ static constexpr int value {2}; };

template<auto I>
requires BoundedByLeftOpenRightClosedInterval<I, 0, 10>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<nullptr>::value == 0);
static_assert(Tester<11>::value == 1);
static_assert(Tester<0>::value == 2);
static_assert(Tester<-1>::value == 2);
static_assert(Tester<3>::value == 3);
static_assert(Tester<10>::value == 3);
/******************************************************************************************************/




}}}}

#endif