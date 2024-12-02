// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SAME_AS_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SAME_AS_H

#include "conceptrodon/descend/varybivore/concepts/same_as.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestSameAs {




/******************************************************************************************************/
template<auto...>
struct Tester
{ static constexpr bool value {false}; };

template<auto I, auto J>
requires SameAs<I, J>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(! Tester<1, 2>::value);
static_assert(Tester<-1, -1>::value);
static_assert(! Tester<1, 1.0>::value);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto I, auto J>
requires SameAs<I, J> && SameAs<J, I>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<-1, -1>::value);
// static_assert(Tester<2, 2>::value);
/******************************************************************************************************/




}}}}

#endif