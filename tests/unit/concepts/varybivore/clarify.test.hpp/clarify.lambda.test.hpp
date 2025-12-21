// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_CLARIFY_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_CLARIFY_H

#include "conceptrodon/concepts/varybivore/clarify.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestClarify {




/******************************************************************************************************/
template<auto Arg>
constexpr auto are_greater_than = [](auto...para)
{ return (...&&(para > Arg)); };

template<auto...>
struct Tester {};

template<auto...Args>
requires Clarify<are_greater_than<0>, Args...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires Clarify<are_greater_than<1>, Args...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires Clarify<are_greater_than<0>, Args...>
&& Clarify<are_greater_than<1>, Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 2, 3>::value == 0);
static_assert(Tester<2, 3, 4>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanOneA
= Clarify<are_greater_than<1>, Args...>;

template<auto...Args>
requires Clarify<are_greater_than<0>, Args...>
&& Clarify<are_greater_than<1>, Args...>
&& GreaterThanOneA<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 2, 4>::value == 0);
static_assert(Tester<2, 3, 4>::value == 1);
// static_assert(Tester<3, 4, 5>::value == 1.1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanOneB
= are_greater_than<1>(Args...);

template<auto...Args>
requires Clarify<are_greater_than<0>, Args...>
&& Clarify<are_greater_than<1>, Args...>
&& GreaterThanOneB<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 2, 5>::value == 0);
static_assert(Tester<2, 3, 4>::value == 1);
static_assert(Tester<3, 4, 5>::value == 1.2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanTwoA
= are_greater_than<2>(Args...);

template<auto...Args>
concept GreaterThanTwoB
= are_greater_than<2>(Args...);

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
= Clarify<are_greater_than<2>, Args...>;

template<auto...Args>
concept GreaterThanTwoD
= Clarify<are_greater_than<2>, Args...>;

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