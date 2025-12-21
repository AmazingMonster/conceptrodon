// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_NO_GREATER_THAN_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_NO_GREATER_THAN_H

#include "conceptrodon/concepts/typelivore/equal_to.hpp"
#include "conceptrodon/concepts/typelivore/less_than.hpp"
#include "conceptrodon/concepts/typelivore/no_greater_than.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestNoGreaterThan {




/******************************************************************************************************/
template<typename, auto>
struct Tester
{ static constexpr int value {0}; };

template<typename I, auto J>
requires NoGreaterThan<I, J>
struct Tester<I, J>
{ static constexpr int value {1}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<1>, 3>::value == 1);
static_assert(Tester<Vay<-1>, -1>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename I, auto J>
requires LessThan<I, J>
struct Tester<I, J>
{ static constexpr int value {2}; };

template<typename I, auto J>
requires EqualTo<I, J>
struct Tester<I, J>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<1>, 3>::value == 1);
static_assert(Tester<Vay<-1>, -1>::value == 1);
static_assert(Tester<Vay<0>, 3>::value == 2);
static_assert(Tester<Vay<1>, 1>::value == 3);
/******************************************************************************************************/




}}}}

#endif