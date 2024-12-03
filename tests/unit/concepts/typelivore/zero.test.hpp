// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ZERO_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ZERO_H

#include "conceptrodon/descend/typelivore/concepts/zero.hpp"
#include "conceptrodon/descend/typelivore/concepts/no_less_than.hpp"
#include "conceptrodon/descend/typelivore/concepts/no_greater_than.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestNegativeOne {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I>
requires NoLessThan<I, 0>
struct Tester<I>
{ static constexpr int value {1}; };

template<typename I>
requires NoGreaterThan<I, 0>
struct Tester<I>
{ static constexpr int value {2}; };

template<typename I>
requires Zero<I>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<nullptr>>::value == 0);
static_assert(Tester<Vay<3>>::value == 1);
static_assert(Tester<Vay<-3>>::value == 2);
static_assert(Tester<Vay<0>>::value == 3);
/******************************************************************************************************/




}}}}

#endif