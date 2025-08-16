// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DECEIVE_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DECEIVE_H

#include "conceptrodon/vay.hpp"
#include "conceptrodon/varybivore/concepts/deceive.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestDeceive {




/******************************************************************************************************/
template<auto Arg>
constexpr bool are_no_greater_than(auto...para)
{ return (...&&(para <= Arg)); }

template<auto...>
struct Tester {};

template<auto...Args>
requires Deceive<are_no_greater_than<0, decltype(Args)...>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires Deceive<are_no_greater_than<1, decltype(Args)...>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires Deceive<are_no_greater_than<0, decltype(Args)...>, Vay<Args>...>
&& Deceive<are_no_greater_than<1, decltype(Args)...>, Vay<Args>...>
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
= Deceive<are_no_greater_than<1, decltype(Args)...>, Vay<Args>...>;


template<auto...Args>
requires Deceive<are_no_greater_than<0, decltype(Args)...>, Vay<Args>...>
&& Deceive<are_no_greater_than<1, decltype(Args)...>, Vay<Args>...>
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
requires Deceive<are_no_greater_than<0, decltype(Args)...>, Vay<Args>...>
&& Deceive<are_no_greater_than<1, decltype(Args)...>, Vay<Args>...>
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
= Deceive<are_no_greater_than<2, decltype(Args)...>, Vay<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= Deceive<are_no_greater_than<2, decltype(Args)...>, Vay<Args>...>;

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