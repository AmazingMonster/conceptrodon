// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_NONZERO_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_NONZERO_H

#include "conceptrodon/concepts/typelivore/all_nonzero.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAllNonzero {




/******************************************************************************************************/
template<typename...>
struct Tester
{ static constexpr bool value {false}; };

template<typename...I>
requires AllNonzero<I...>
struct Tester<I...>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vay<1>, Vay<2>, Vay<3>>::value);
static_assert(! Tester<Vay<-1>, Vay<0>, Vay<-1>>::value);
static_assert(! Tester<Vay<0>, Vay<0>, Vay<0>>::value);
/******************************************************************************************************/




}}}}

#endif