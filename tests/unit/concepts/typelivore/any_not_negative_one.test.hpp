// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_NOT_NEGATIVE_ONE_H

#include "conceptrodon/typelivore/concepts/all_not_negative_one.hpp"
#include "conceptrodon/typelivore/concepts/any_not_negative_one.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAnyNegativeOne {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename...I>
requires AnyNotNegativeOne<I...>
struct Tester<I...>
{ static constexpr int value {1}; };

template<typename...I>
requires AllNotNegativeOne<I...>
struct Tester<I...>
{ static constexpr int value {2}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<-1>, Vay<-1>, Vay<-1>>::value == 0);
static_assert(Tester<Vay<-1>, Vay<1>, Vay<-1>>::value == 1);
static_assert(Tester<Vay<1>, Vay<2>, Vay<3>>::value == 2);
/******************************************************************************************************/




}}}}

#endif