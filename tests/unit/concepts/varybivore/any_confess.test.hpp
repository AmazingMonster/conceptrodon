// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ANY_CONFESS_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ANY_CONFESS_H

#include "conceptrodon/utilities/vay.hpp"
#include "conceptrodon/varybivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAnyConfess {




/******************************************************************************************************/
template<auto Arg>
constexpr bool are_greater_than(int para)
{ return para > Arg; }
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AnyConfess<are_greater_than<0>, Vay<1>, Vay<2>, Vay<3>>);
static_assert(AnyConfess<are_greater_than<0>, Vay<1>, Vay<-2>, Vay<-3>>);
static_assert(! AnyConfess<are_greater_than<0>, Vay<0>, Vay<-1>, Vay<-2>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AnyConfess<are_greater_than<0>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AnyConfess<are_greater_than<1>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AnyConfess<are_greater_than<0>, Vay<Args>...>
&& AnyConfess<are_greater_than<1>, Vay<Args>...>
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
= AnyConfess<are_greater_than<1>, Vay<Args>...>;

template<auto...Args>
requires AnyConfess<are_greater_than<0>, Vay<Args>...>
&& AnyConfess<are_greater_than<1>, Vay<Args>...>
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
= (...||(are_greater_than<1>(Args)));

template<auto...Args>
requires AnyConfess<are_greater_than<0>, Vay<Args>...>
&& AnyConfess<are_greater_than<1>, Vay<Args>...>
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
= (...||(are_greater_than<2>(Args)));

template<auto...Args>
concept GreaterThanTwoB
= (...||(are_greater_than<2>(Args)));

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

static_assert(TesterB<3, 4, 5>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanTwoC
= AnyConfess<are_greater_than<2>, Vay<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= AnyConfess<are_greater_than<2>, Vay<Args>...>;

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

// static_assert(TesterC<3, 4, 5>::value == 2);
/******************************************************************************************************/




}}}}

#endif