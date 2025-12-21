// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_LESS_THAN_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_LESS_THAN_H

#include "conceptrodon/metafunctions/typelivore/concepts/less_than.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestLessThan {




/******************************************************************************************************/
template<typename, auto>
struct Tester
{ static constexpr bool value {false}; };

template<typename I, auto J>
requires LessThan<I, J>
struct Tester<I, J>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<1>, 2>::value);
static_assert(! Tester<Vay<-1>, -1>::value);
static_assert(! Tester<Vay<1>, 1.0>::value);
static_assert(Tester<Vay<1>, 2.0>::value);
/******************************************************************************************************/




}}}}

#endif