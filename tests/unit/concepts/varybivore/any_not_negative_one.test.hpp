// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ANY_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ANY_NOT_NEGATIVE_ONE_H

#include "conceptrodon/varybivore/concepts/any_not_negative_one.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAnyNegativeOne {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto...I>
requires AnyNotNegativeOne<I...>
struct Tester<I...>
{ static constexpr int value {1}; };

template<auto...I>
requires AllNotNegativeOne<I...>
struct Tester<I...>
{ static constexpr int value {2}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<-1, -1, -1>::value == 0);
static_assert(Tester<-1, 1, -1>::value == 1);
static_assert(Tester<1, 2, 3>::value == 2);
/******************************************************************************************************/




}}}}

#endif