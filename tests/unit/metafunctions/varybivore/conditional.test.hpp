// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CONDITIONAL_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CONDITIONAL_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/varybivore/conditional.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestConditional {




/******************************************************************************************************/
struct VoidInt;

template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

template<auto...>
struct PositiveTester: public std::false_type {};

template<auto I>
requires (0 < I)
struct PositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};
/******************************************************************************************************/




/******************************************************************************************************/
INVALID(Conditional<1, 0>::Road<VoidTester, IntTester>::Mold<int>::value);
INVALID(Conditional<1, 0>::Road<VoidTester, IntTester>::Mold<void>::value);
INVALID(Conditional<1, 0>::Rail<PositiveTester, NonnegativeTester>::Page<0>::value);
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Conditional<1, 0>::Road<VoidTester, IntTester>::Mold<VoidInt>::value);
VALID(Conditional<1, 0>::Rail<PositiveTester, NonnegativeTester>::Page<1>::value);
VALID(Conditional<1, 0>::Road<>::Mold<VoidInt>::value);
VALID(Conditional<1, 0>::Rail<>::Page<1>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif