// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_BOUNDED_BY_OPEN_INTERVAL_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_BOUNDED_BY_OPEN_INTERVAL_H

#include "conceptrodon/descend/typelivore/concepts/bounded_by_open_interval.hpp"
#include "conceptrodon/descend/typelivore/concepts/greater_than.hpp"
#include "conceptrodon/descend/typelivore/concepts/less_than.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestBoundedByOpenInterval {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I>
requires LessThan<I, 10>
struct Tester<I>
{ static constexpr int value {1}; };

template<typename I>
requires GreaterThan<I, 0>
struct Tester<I>
{ static constexpr int value {2}; };

template<typename I>
requires BoundedByOpenInterval<I, 0, 10>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<nullptr>>::value == 0);
static_assert(Tester<Monotony<0>>::value == 1);
static_assert(Tester<Monotony<11>>::value == 2);
static_assert(Tester<Monotony<1>>::value == 3);
/******************************************************************************************************/




}}}}

#endif