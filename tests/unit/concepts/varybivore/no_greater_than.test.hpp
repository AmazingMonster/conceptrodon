// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_NO_GREATER_THAN_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_NO_GREATER_THAN_H

#include "conceptrodon/varybivore/concepts/descend/no_greater_than.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestNoGreaterThan {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto I, auto J>
requires NoGreaterThan<I, J>
struct Tester<I, J>
{ static constexpr int value {1}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 3>::value == 1);
static_assert(Tester<-1, -1>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J>
requires LessThan<I, J>
struct Tester<I, J>
{ static constexpr int value {2}; };

template<auto I, auto J>
requires EqualTo<I, J>
struct Tester<I, J>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 3>::value == 1);
static_assert(Tester<-1, -1>::value == 1);
static_assert(Tester<0, 3>::value == 2);
static_assert(Tester<1, 1>::value == 3);
/******************************************************************************************************/




}}}}

#endif