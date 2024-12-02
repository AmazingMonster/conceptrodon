// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_ZERO_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_ZERO_H

#include "conceptrodon/descend/typelivore/concepts/all_zero.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAllZero {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr bool value {false}; };

template<typename...I>
requires AllZero<I...>
struct Tester<I...>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(! Tester<Monotony<1>, Monotony<2>, Monotony<3>>::value);
static_assert(! Tester<Monotony<-1>, Monotony<0>, Monotony<-1>>::value);
static_assert(Tester<Monotony<0>, Monotony<0>, Monotony<0>>::value);
/******************************************************************************************************/




}}}}

#endif