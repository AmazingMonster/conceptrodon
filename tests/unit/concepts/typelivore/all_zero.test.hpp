// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_ZERO_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_ZERO_H

#include "conceptrodon/typelivore/concepts/all_zero.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAllZero {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr bool value {false}; };

template<typename...I>
requires AllZero<I...>
struct Tester<I...>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(! Tester<Vay<1>, Vay<2>, Vay<3>>::value);
static_assert(! Tester<Vay<-1>, Vay<0>, Vay<-1>>::value);
static_assert(Tester<Vay<0>, Vay<0>, Vay<0>>::value);
/******************************************************************************************************/




}}}}

#endif