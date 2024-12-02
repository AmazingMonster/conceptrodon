// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_DIFFERENT_FROM_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_DIFFERENT_FROM_H

#include "conceptrodon/descend/typelivore/concepts/different_from.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestDifferentFrom {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr bool value {false}; };

template<typename I, typename J>
requires DifferentFrom<I, J>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<1>, Monotony<2>>::value);
static_assert(! Tester<Monotony<-1>, Monotony<-1>>::value);
static_assert(Tester<Monotony<1>, Monotony<1.0>>::value);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename I, typename J>
requires DifferentFrom<J, I>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<1>, Monotony<2>>::value);
// static_assert(Tester<Monotony<2>, Monotony<2.0>>::value);
/******************************************************************************************************/




}}}}

#endif