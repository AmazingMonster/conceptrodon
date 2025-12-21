// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ALL_NEGATIVE_ONE_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ALL_NEGATIVE_ONE_H

#include "conceptrodon/concepts/varybivore/all_negative_one.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAllNegativeOne {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr bool value {false}; };

template<auto...I>
requires AllNegativeOne<I...>
struct Tester<I...>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(! Tester<1, 2, 3>::value);
static_assert(Tester<-1, -1, -1>::value);
/******************************************************************************************************/




}}}}

#endif