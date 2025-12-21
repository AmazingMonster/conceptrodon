// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_BOUNDED_BY_OPEN_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_BOUNDED_BY_OPEN_INTERVAL_H

#include "conceptrodon/concepts/varybivore/bounded_by_open_interval.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestBoundedByOpenInterval {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto I>
requires LessThan<I, 10>
struct Tester<I>
{ static constexpr int value {1}; };

template<auto I>
requires LessThan<0, I>
struct Tester<I>
{ static constexpr int value {2}; };

template<auto I>
requires BoundedByOpenInterval<I, 0, 10>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<nullptr>::value == 0);
static_assert(Tester<0>::value == 1);
static_assert(Tester<11>::value == 2);
static_assert(Tester<1>::value == 3);
/******************************************************************************************************/




}}}}

#endif