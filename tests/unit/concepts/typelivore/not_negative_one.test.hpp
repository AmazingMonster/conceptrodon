// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_NOT_NEGATIVE_ONE_H

#include "conceptrodon/descend/typelivore/concepts/less_than.hpp"
#include "conceptrodon/descend/typelivore/concepts/not_negative_one.hpp"
#include "conceptrodon/descend/typelivore/concepts/greater_than.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestNoLessThan {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I>
requires NotNegativeOne<I>
struct Tester<I>
{ static constexpr int value {1}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<-1>>::value == 0);
static_assert(Tester<Monotony<1>>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename I>
requires GreaterThan<I, -1>
struct Tester<I>
{ static constexpr int value {2}; };

template<typename I>
requires LessThan<I, -1>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<-1>>::value == 0);
static_assert(Tester<Monotony<1>>::value == 1);
static_assert(Tester<Monotony<2>>::value == 2);
static_assert(Tester<Monotony<-2>>::value == 3);
/******************************************************************************************************/




}}}}

#endif