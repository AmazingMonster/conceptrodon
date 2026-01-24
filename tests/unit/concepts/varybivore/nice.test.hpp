// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_NICE_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_NICE_H

#include "conceptrodon/concepts/varybivore/nice.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestNice {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto I, auto J>
requires Nice<I.value>
struct Tester<I, J>
{ static constexpr int value {1}; };

template<auto I, auto J>
requires Nice<I.value> && Nice<J.value>
struct Tester<I, J>
{ static constexpr int value {2}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<0>::value == 0);
static_assert(Tester<std::integral_constant<int, 0>{}, 0>::value == 1);
static_assert(Tester<std::integral_constant<int, 0>{}, std::integral_constant<int, 0>{}>::value == 2);
/******************************************************************************************************/




}}}}

#endif