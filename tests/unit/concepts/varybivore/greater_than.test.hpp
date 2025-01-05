// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_GREATER_THAN_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_GREATER_THAN_H

#include "conceptrodon/varybivore/concepts/greater_than.hpp"
#include "conceptrodon/varybivore/concepts/less_than.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestGreaterThan {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr bool value {false}; };

template<auto I, auto J>
requires GreaterThan<I, J>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<3, 2>::value);
static_assert(! Tester<-1, -1>::value);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J>
requires LessThan<J, I>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<3, 2>::value);
// static_assert(Tester<4, 2>::value);
/******************************************************************************************************/




}}}}

#endif