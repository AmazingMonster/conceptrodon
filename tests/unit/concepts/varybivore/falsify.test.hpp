// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_FALSIFY_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_FALSIFY_H

#include "conceptrodon/varybivore/concepts/falsify.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestFalsify {




/******************************************************************************************************/
template<auto Arg>
constexpr bool are_no_greater_than(auto...para)
{ return (...&&(para <= Arg)); }

template<auto...>
struct Tester {};

template<auto...Args>
requires Falsify<are_no_greater_than<0, decltype(Args)...>, Args...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires Falsify<are_no_greater_than<1, decltype(Args)...>, Args...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires Falsify<are_no_greater_than<0, decltype(Args)...>, Args...>
&& Falsify<are_no_greater_than<1, decltype(Args)...>, Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1>::value == 0);
static_assert(Tester<2>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanOneA
= Falsify<are_no_greater_than<1, decltype(Args)...>, Args...>;


template<auto...Args>
requires Falsify<are_no_greater_than<0, decltype(Args)...>, Args...>
&& Falsify<are_no_greater_than<1, decltype(Args)...>, Args...>
&& GreaterThanOneA<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<0.9>::value == 0);
static_assert(Tester<2>::value == 1);
// static_assert(Tester<3>::value == 1.1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanOneB
= not are_no_greater_than<1>(Args...);

template<auto...Args>
requires Falsify<are_no_greater_than<0, decltype(Args)...>, Args...>
&& Falsify<are_no_greater_than<1, decltype(Args)...>, Args...>
&& GreaterThanOneB<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<0.8>::value == 0);
static_assert(Tester<2>::value == 1);
static_assert(Tester<3>::value == 1.2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanTwoA
= not are_no_greater_than<2>(Args...);

template<auto...Args>
concept GreaterThanTwoB
= not are_no_greater_than<2>(Args...);

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

static_assert(TesterB<3>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanTwoC
= Falsify<are_no_greater_than<2, decltype(Args)...>, Args...>;

template<auto...Args>
concept GreaterThanTwoD
= Falsify<are_no_greater_than<2, decltype(Args)...>, Args...>;

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

// static_assert(TesterC<3>::value == 2);
/******************************************************************************************************/




}}}}

#endif