// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DIFFERENT_FROM_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DIFFERENT_FROM_H

#include "conceptrodon/concepts/varybivore/different_from.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestDifferentFrom {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr bool value {false}; };

template<auto I, auto J>
requires DifferentFrom<I, J>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 2>::value);
static_assert(! Tester<-1, -1>::value);
static_assert(Tester<1, 1.0>::value);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J>
requires DifferentFrom<I, J> && DifferentFrom<J, I>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 2>::value);
// static_assert(Tester<2, 2.0>::value);
/******************************************************************************************************/




}}}}

#endif