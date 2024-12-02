// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_NEGATIVE_ONE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_NEGATIVE_ONE_H

#include "conceptrodon/descend/typelivore/concepts/negative_one.hpp"
#include "conceptrodon/descend/typelivore/concepts/no_less_than.hpp"
#include "conceptrodon/descend/typelivore/concepts/no_greater_than.hpp"
#include "conceptrodon/monotony.hpp"

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
static_assert(Tester<Monotony<nullptr>>::value == 0);
static_assert(Tester<Monotony<3>>::value == 1);
static_assert(Tester<Monotony<-3>>::value == 2);
static_assert(Tester<Monotony<-1>>::value == 3);
/******************************************************************************************************/




}}}}

#endif