// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_LESS_THAN_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_LESS_THAN_H

#include "conceptrodon/varybivore/concepts/less_than.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestLessThan {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr bool value {false}; };

template<auto I, auto J>
requires LessThan<I, J>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 2>::value);
static_assert(! Tester<-1, -1>::value);
static_assert(! Tester<1, 1.0>::value);
static_assert(Tester<1, 2.0>::value);
/******************************************************************************************************/




}}}}

#endif