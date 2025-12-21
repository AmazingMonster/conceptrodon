// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_NONZERO_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_NONZERO_H

#include "conceptrodon/concepts/varybivore/nonzero.hpp"
#include "conceptrodon/concepts/varybivore/greater_than.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestNoLessThan {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto I>
requires Nonzero<I>
struct Tester<I>
{ static constexpr int value {1}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<0>::value == 0);
static_assert(Tester<1>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I>
requires GreaterThan<I, 0>
struct Tester<I>
{ static constexpr int value {2}; };

template<auto I>
requires LessThan<I, 0>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<0>::value == 0);
static_assert(Tester<1>::value == 1);
static_assert(Tester<2>::value == 2);
static_assert(Tester<-1>::value == 3);
/******************************************************************************************************/




}}}}

#endif