// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_EQUAL_TO_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_EQUAL_TO_H

#include "conceptrodon/concepts/varybivore/equal_to.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestEqualTo {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr bool value {false}; };

template<auto I, auto J>
requires EqualTo<I, J>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(! Tester<1, 2>::value);
static_assert(Tester<-1, -1>::value);
static_assert(Tester<1, 1.0>::value);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J>
requires EqualTo<J, I>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 1.0>::value);
// static_assert(Tester<2, 2.0>::value);
/******************************************************************************************************/




}}}}

#endif