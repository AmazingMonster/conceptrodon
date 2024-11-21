// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_CONDITIONAL_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_CONDITIONAL_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/typelivore/any_conditional.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAnyConditional {




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
#define SUPPOSED_TYPE   \
    std::false_type

SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Road<VoidTester, IntTester>::Mold<int*>);
SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Road<VoidTester, IntTester>::Mold<void*>);
SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Rail<PositiveTester, NonnegativeTester>::Page<-1>);
SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Road<>::Mold<VoidInt>);
SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Rail<>::Page<1>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::true_type

SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Road<VoidTester, IntTester>::Mold<VoidInt>);
SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Rail<PositiveTester, NonnegativeTester>::Page<1>);
SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Road<VoidTester, IntTester>::Mold<int>);
SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Road<VoidTester, IntTester>::Mold<void>);
SAME_TYPE(AnyConditional<std::true_type, std::false_type>::Rail<PositiveTester, NonnegativeTester>::Page<0>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif