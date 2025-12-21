// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_UNEQUAL_TO_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_UNEQUAL_TO_H

#include "conceptrodon/concepts/varybivore/unequal_to.hpp"
#include "conceptrodon/concepts/varybivore/greater_than.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestNoLessThan {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto I, auto J>
requires UnequalTo<I, J>
struct Tester<I, J>
{ static constexpr int value {1}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<3, 1>::value == 1);
static_assert(Tester<-1, -1>::value == 0);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J>
requires GreaterThan<I, J>
struct Tester<I, J>
{ static constexpr int value {2}; };

template<auto I, auto J>
requires LessThan<I, J>
struct Tester<I, J>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<-1, -1>::value == 0);
static_assert(Tester<3, 1>::value == 1);
static_assert(Tester<3, 0>::value == 2);
static_assert(Tester<1, 3>::value == 3);
/******************************************************************************************************/




}}}}

#endif