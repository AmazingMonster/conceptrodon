// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_NEGATIVE_ONE_H

#include "conceptrodon/concepts/typelivore/negative_one.hpp"
#include "conceptrodon/concepts/typelivore/no_less_than.hpp"
#include "conceptrodon/concepts/typelivore/no_greater_than.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestNegativeOne {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I>
requires NoLessThan<I, -1>
struct Tester<I>
{ static constexpr int value {1}; };

template<typename I>
requires NoGreaterThan<I, -1>
struct Tester<I>
{ static constexpr int value {2}; };

template<typename I>
requires NegativeOne<I>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<nullptr>>::value == 0);
static_assert(Tester<Vay<3>>::value == 1);
static_assert(Tester<Vay<-3>>::value == 2);
static_assert(Tester<Vay<-1>>::value == 3);
/******************************************************************************************************/




}}}}

#endif