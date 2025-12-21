// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_NOT_NEGATIVE_ONE_H

#include "conceptrodon/concepts/typelivore/all_not_negative_one.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAllNotNegativeOne {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr bool value {false}; };

template<typename...I>
requires AllNotNegativeOne<I...>
struct Tester<I...>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<1>, Vay<2>, Vay<3>>::value);
static_assert(! Tester<Vay<-1>, Vay<-1>, Vay<-1>>::value);
/******************************************************************************************************/




}}}}

#endif