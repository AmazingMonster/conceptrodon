// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_NONZERO_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_NONZERO_H

#include "conceptrodon/typelivore/concepts/all_nonzero.hpp"
#include "conceptrodon/typelivore/concepts/any_nonzero.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAnyNonzero {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename...I>
requires AnyNonzero<I...>
struct Tester<I...>
{ static constexpr int value {1}; };

template<typename...I>
requires AllNonzero<I...>
struct Tester<I...>
{ static constexpr int value {2}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<0>, Vay<0>, Vay<0>>::value == 0);
static_assert(Tester<Vay<-1>, Vay<0>, Vay<-1>>::value == 1);
static_assert(Tester<Vay<1>, Vay<2>, Vay<3>>::value == 2);
/******************************************************************************************************/




}}}}

#endif