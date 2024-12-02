// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_NEGATIVE_ONE_H

#include "conceptrodon/descend/typelivore/concepts/all_negative_one.hpp"
#include "conceptrodon/descend/typelivore/concepts/any_negative_one.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAnyNegativeOne {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename...I>
requires AnyNegativeOne<I...>
struct Tester<I...>
{ static constexpr int value {1}; };

template<typename...I>
requires AllNegativeOne<I...>
struct Tester<I...>
{ static constexpr int value {2}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<1>, Monotony<2>, Monotony<3>>::value == 0);
static_assert(Tester<Monotony<-1>, Monotony<1>, Monotony<-1>>::value == 1);
static_assert(Tester<Monotony<-1>, Monotony<-1>, Monotony<-1>>::value == 2);
/******************************************************************************************************/




}}}}

#endif