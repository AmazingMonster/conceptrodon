// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_NEGATIVE_ONE_H

#include "conceptrodon/typelivore/concepts/all_negative_one.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAllNegativeOne {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr bool value {false}; };

template<typename...Vay>
requires AllNegativeOne<Vay...>
struct Tester<Vay...>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(! Tester<Vay<1>, Vay<2>, Vay<3>>::value);
static_assert(Tester<Vay<-1>, Vay<-1>, Vay<-1>>::value);
/******************************************************************************************************/




}}}}

#endif