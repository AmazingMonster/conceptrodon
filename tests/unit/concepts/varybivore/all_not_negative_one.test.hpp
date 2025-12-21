// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ALL_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ALL_NOT_NEGATIVE_ONE_H

#include "conceptrodon/concepts/varybivore/all_not_negative_one.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAllNotNegativeOne {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr bool value {false}; };

template<auto...I>
requires AllNotNegativeOne<I...>
struct Tester<I...>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 2, 3>::value);
static_assert(! Tester<-1, -1, -1>::value);
/******************************************************************************************************/




}}}}

#endif