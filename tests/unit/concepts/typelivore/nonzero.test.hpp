// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_NONZERO_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_NONZERO_H

#include "conceptrodon/concepts/typelivore/less_than.hpp"
#include "conceptrodon/concepts/typelivore/nonzero.hpp"
#include "conceptrodon/concepts/typelivore/greater_than.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestNoLessThan {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I>
requires Nonzero<I>
struct Tester<I>
{ static constexpr int value {1}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<0>>::value == 0);
static_assert(Tester<Vay<1>>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename I>
requires GreaterThan<I, 0>
struct Tester<I>
{ static constexpr int value {2}; };

template<typename I>
requires LessThan<I, 0>
struct Tester<I>
{ static constexpr int value {3}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<0>>::value == 0);
static_assert(Tester<Vay<1>>::value == 1);
static_assert(Tester<Vay<2>>::value == 2);
static_assert(Tester<Vay<-1>>::value == 3);
/******************************************************************************************************/




}}}}

#endif