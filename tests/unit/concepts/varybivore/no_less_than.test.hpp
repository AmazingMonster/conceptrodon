// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_NO_LESS_THAN_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_NO_LESS_THAN_H

#include "conceptrodon/concepts/varybivore/no_less_than.hpp"
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
requires NoLessThan<I, J>
struct Tester<I, J>
{ static constexpr int value {1}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<3, 1>::value == 1);
static_assert(Tester<-1, -1>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J>
requires GreaterThan<I, J>
struct Tester<I, J>
{ static constexpr int value {2}; };

template<auto I, auto J>
requires EqualTo<I, J>
struct Tester<I, J>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<3, 1>::value == 1);
static_assert(Tester<-1, -1>::value == 1);
static_assert(Tester<3, 0>::value == 2);
static_assert(Tester<1, 1>::value == 3);
/******************************************************************************************************/




}}}}

#endif