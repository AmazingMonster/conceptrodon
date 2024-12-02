// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_GREATER_THAN_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_GREATER_THAN_H

#include "conceptrodon/descend/typelivore/concepts/greater_than.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestGreaterThan {




/******************************************************************************************************/
template<typename, auto>
struct Tester
{ static constexpr bool value {false}; };

template<typename I, auto J>
requires GreaterThan<I, J>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<3>, 2>::value);
static_assert(! Tester<Monotony<-1>, -1>::value);
/******************************************************************************************************/




}}}}

#endif