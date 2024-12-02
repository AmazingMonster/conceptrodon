// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_NOT_NEGATIVE_ONE_H

#include "conceptrodon/descend/typelivore/concepts/all_not_negative_one.hpp"
#include "conceptrodon/monotony.hpp"

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
static_assert(Tester<Monotony<1>, Monotony<2>, Monotony<3>>::value);
static_assert(! Tester<Monotony<-1>, Monotony<-1>, Monotony<-1>>::value);
/******************************************************************************************************/




}}}}

#endif