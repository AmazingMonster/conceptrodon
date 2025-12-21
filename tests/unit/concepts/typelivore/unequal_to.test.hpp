// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_UNEQUAL_TO_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_UNEQUAL_TO_H

#include "conceptrodon/metafunctions/typelivore/concepts/less_than.hpp"
#include "conceptrodon/metafunctions/typelivore/concepts/unequal_to.hpp"
#include "conceptrodon/metafunctions/typelivore/concepts/greater_than.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestNoLessThan {




/******************************************************************************************************/
template<typename, auto>
struct Tester
{ static constexpr int value {0}; };

template<typename I, auto J>
requires UnequalTo<I, J>
struct Tester<I, J>
{ static constexpr int value {1}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<3>, 1>::value == 1);
static_assert(Tester<Vay<-1>, -1>::value == 0);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename I, auto J>
requires GreaterThan<I, J>
struct Tester<I, J>
{ static constexpr int value {2}; };

template<typename I, auto J>
requires LessThan<I, J>
struct Tester<I, J>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<-1>, -1>::value == 0);
static_assert(Tester<Vay<3>, 1>::value == 1);
static_assert(Tester<Vay<3>, 0>::value == 2);
static_assert(Tester<Vay<1>, 3>::value == 3);
/******************************************************************************************************/




}}}}

#endif