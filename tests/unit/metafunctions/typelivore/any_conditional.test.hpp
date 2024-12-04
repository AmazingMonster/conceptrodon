// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_CONDITIONAL_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_CONDITIONAL_H

#include <utility>

#include "conceptrodon/typelivore/any_conditional.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAnyConditional {




/******************************************************************************************************/
struct IfTrue {};

struct IfFalse {};

using Select = AnyConditional<IfTrue, IfFalse>;
/******************************************************************************************************/




/**** First Test ****/
/******************************************************************************************************/
static_assert(std::same_as<Select::Page<1, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 0>, IfFalse>);
/******************************************************************************************************/




/**** Second Test ****/
/******************************************************************************************************/
static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 0>
    >, 
    IfFalse
>);
/******************************************************************************************************/




/**** Third Test ****/
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

template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

static_assert(std::same_as<Metafunction<int>, IfTrue>);
static_assert(std::same_as<Metafunction<void>, IfTrue>);
static_assert(std::same_as<Metafunction<VoidInt>, IfTrue>);
static_assert(std::same_as<Metafunction<double>, IfFalse>);
static_assert(std::same_as<Select::Road<>::Mold<>, IfFalse>);
/******************************************************************************************************/




/**** Fourth Test ****/
/******************************************************************************************************/
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0 )
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

static_assert(std::same_as<Metafunction_1<1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<-1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<0>, IfTrue>);
static_assert(std::same_as<Metafunction_1<nullptr>, IfFalse>);
static_assert(std::same_as<Select::Rail<>::Page<>, IfFalse>);
/******************************************************************************************************/




}}}}

#endif