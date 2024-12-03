// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_ZERO_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_ZERO_H

#include "conceptrodon/descend/typelivore/concepts/all_zero.hpp"
#include "conceptrodon/descend/typelivore/concepts/any_zero.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAnyZero {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename...I>
requires AnyZero<I...>
struct Tester<I...>
{ static constexpr int value {1}; };

template<typename...I>
requires AllZero<I...>
struct Tester<I...>
{ static constexpr int value {2}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<-1>, Vay<-1>, Vay<-1>>::value == 0);
static_assert(Tester<Vay<-1>, Vay<1>, Vay<0>>::value == 1);
static_assert(Tester<Vay<0>, Vay<0>, Vay<0>>::value == 2);
/******************************************************************************************************/




}}}}

#endif