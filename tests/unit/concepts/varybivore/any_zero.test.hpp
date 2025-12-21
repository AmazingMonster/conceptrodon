// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ANY_ZERO_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ANY_ZERO_H

#include "conceptrodon/concepts/varybivore/any_zero.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAnyZero {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto...I>
requires AnyZero<I...>
struct Tester<I...>
{ static constexpr int value {1}; };

template<auto...I>
requires AllZero<I...>
struct Tester<I...>
{ static constexpr int value {2}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<-1, -1, -1>::value == 0);
static_assert(Tester<-1, 1, 0>::value == 1);
static_assert(Tester<0, 0, 0>::value == 2);
/******************************************************************************************************/




}}}}

#endif