// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_EQUAL_TO_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_EQUAL_TO_H

#include "conceptrodon/descend/typelivore/concepts/equal_to.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestEqualTo {




/******************************************************************************************************/
template<typename, auto>
struct Tester
{ static constexpr bool value {false}; };

template<typename I, auto J>
requires EqualTo<I, J>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(! Tester<Monotony<1>, 2>::value);
static_assert(Tester<Monotony<-1>, -1>::value);
static_assert(Tester<Monotony<1>, 1.0>::value);
/******************************************************************************************************/




}}}}

#endif