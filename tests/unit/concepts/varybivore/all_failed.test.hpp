// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ALL_FAILED_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ALL_FAILED_H

#include "conceptrodon/concepts/varybivore/all_failed.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAllFailed {




/******************************************************************************************************/
template<auto Arg>
constexpr bool are_no_greater_than(int para)
{ return para <= Arg; }
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AllFailed<are_no_greater_than<0>, 1, 2, 3>);
static_assert(! AllFailed<are_no_greater_than<0>, 0, 2, 3>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AllFailed<are_no_greater_than<0>, Args...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AllFailed<are_no_greater_than<1>, Args...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AllFailed<are_no_greater_than<0>, Args...>
&& AllFailed<are_no_greater_than<1>, Args...>
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
= AllFailed<are_no_greater_than<1>, Args...>;

template<auto...Args>
requires AllFailed<are_no_greater_than<0>, Args...>
&& AllFailed<are_no_greater_than<1>, Args...>
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
= (...&&(not are_no_greater_than<1>(Args)));

template<auto...Args>
requires AllFailed<are_no_greater_than<0>, Args...>
&& AllFailed<are_no_greater_than<1>, Args...>
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
= (...&&(not are_no_greater_than<2>(Args)));

template<auto...Args>
concept GreaterThanTwoB
= (...&&(not are_no_greater_than<2>(Args)));

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
= AllFailed<are_no_greater_than<2>, Args...>;

template<auto...Args>
concept GreaterThanTwoD
= AllFailed<are_no_greater_than<2>, Args...>;

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