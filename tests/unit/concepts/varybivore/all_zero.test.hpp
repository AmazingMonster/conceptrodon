// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ALL_ZERO_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ALL_ZERO_H

#include "conceptrodon/concepts/varybivore/all_zero.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAllZero {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr bool value {false}; };

template<auto...I>
requires AllZero<I...>
struct Tester<I...>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(! Tester<1, 2, 3>::value);
static_assert(! Tester<-1, 0, -1>::value);
static_assert(Tester<0, 0, 0>::value);
/******************************************************************************************************/




}}}}

#endif