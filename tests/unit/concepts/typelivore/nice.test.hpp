// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_NICE_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_NICE_H

#include "conceptrodon/concepts/typelivore/nice.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestNice {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I, typename J>
requires Nice<typename I::type>
struct Tester<I, J>
{ static constexpr int value {1}; };

template<typename I, typename J>
requires Nice<typename I::type> && Nice<typename J::type>
struct Tester<I, J>
{ static constexpr int value {2}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, std::type_identity<int>>::value == 0);
static_assert(Tester<std::type_identity<int>, int>::value == 1);
static_assert(Tester<std::type_identity<int>, std::type_identity<int>>::value == 2);
/******************************************************************************************************/




}}}}

#endif