// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ANY_CONFESS_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ANY_CONFESS_H

#include "conceptrodon/pagelivore/concepts/any_confess.hpp"
#include "conceptrodon/vay.hpp"
#include "conceptrodon/varybivore/are_greater_than.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestAnyConfess {




/******************************************************************************************************/
static_assert(AnyConfess<Varybivore::AreGreaterThan<0>::Page, Vay<1>, Vay<2>, Vay<3>>);
static_assert(AnyConfess<Varybivore::AreGreaterThan<0>::Page, Vay<1>, Vay<-2>, Vay<-3>>);
static_assert(! AnyConfess<Varybivore::AreGreaterThan<0>::Page, Vay<0>, Vay<-1>, Vay<-2>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AnyConfess<Varybivore::AreGreaterThan<0>::Page, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AnyConfess<Varybivore::AreGreaterThan<1>::Page, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AnyConfess<Varybivore::AreGreaterThan<0>::Page, Vay<Args>...>
&& AnyConfess<Varybivore::AreGreaterThan<1>::Page, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, -2, -3>::value == 0);
static_assert(Tester<2, -3, -4>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanOneA
= AnyConfess<Varybivore::AreGreaterThan<1>::Page, Vay<Args>...>;


template<auto...Args>
requires AnyConfess<Varybivore::AreGreaterThan<0>::Page, Vay<Args>...>
&& AnyConfess<Varybivore::AreGreaterThan<1>::Page, Vay<Args>...>
&& GreaterThanOneA<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, -2, -4>::value == 0);
static_assert(Tester<2, -3, -4>::value == 1);
// static_assert(Tester<3, -4, -5>::value == 1.1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanOneB
= (...||(Varybivore::AreGreaterThan<1>::Page<Args>::value));

template<auto...Args>
requires AnyConfess<Varybivore::AreGreaterThan<0>::Page, Vay<Args>...>
&& AnyConfess<Varybivore::AreGreaterThan<1>::Page, Vay<Args>...>
&& GreaterThanOneB<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, -2, -5>::value == 0);
static_assert(Tester<2, -3, -4>::value == 1);
static_assert(Tester<3, -4, -5>::value == 1.2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanTwoA
= (...||(Varybivore::AreGreaterThan<1>::Page<Args>::value));

template<auto...Args>
concept GreaterThanTwoB
= (...||(Varybivore::AreGreaterThan<1>::Page<Args>::value));

template<auto...>
struct TesterB;

template<auto...Args>
requires GreaterThanTwoA<Args...>
struct TesterB<Args...>
{
    static constexpr int value {-2};
};

template<auto...Args>
requires GreaterThanTwoA<Args...>
&& GreaterThanTwoB<Args...>
struct TesterB<Args...>
{
    static constexpr int value {2};
};

static_assert(TesterB<3, -4, -5>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanTwoC
= AnyConfess<Varybivore::AreGreaterThan<2>::Page, Vay<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= AnyConfess<Varybivore::AreGreaterThan<2>::Page, Vay<Args>...>;

template<auto...>
struct TesterC;

template<auto...Args>
requires GreaterThanTwoC<Args...>
struct TesterC<Args...>
{
    static constexpr int value {-2};
};

template<auto...Args>
requires GreaterThanTwoC<Args...>
&& GreaterThanTwoD<Args...>
struct TesterC<Args...>
{
    static constexpr int value {2};
};

// static_assert(TesterC<3, -4, -5>::value == 2);
/******************************************************************************************************/




}}}}

#endif