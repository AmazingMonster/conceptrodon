// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ZERO_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ZERO_H

#include "conceptrodon/metafunctions/varybivore/concepts/zero.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/no_less_than.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/no_greater_than.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestNegativeOne {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto I>
requires NoLessThan<I, 0>
struct Tester<I>
{ static constexpr int value {1}; };

template<auto I>
requires NoGreaterThan<I, 0>
struct Tester<I>
{ static constexpr int value {2}; };

template<auto I>
requires Zero<I>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<nullptr>::value == 0);
static_assert(Tester<3>::value == 1);
static_assert(Tester<-3>::value == 2);
static_assert(Tester<0>::value == 3);
/******************************************************************************************************/




}}}}

#endif