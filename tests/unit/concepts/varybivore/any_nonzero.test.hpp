// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ANY_NONZERO_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ANY_NONZERO_H

#include "conceptrodon/concepts/varybivore/any_nonzero.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAnyNonzero {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto...I>
requires AnyNonzero<I...>
struct Tester<I...>
{ static constexpr int value {1}; };

template<auto...I>
requires AllNonzero<I...>
struct Tester<I...>
{ static constexpr int value {2}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<0, 0, 0>::value == 0);
static_assert(Tester<-1, 0, -1>::value == 1);
static_assert(Tester<1, 2, 3>::value == 2);
/******************************************************************************************************/




}}}}

#endif