// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_ALL_PASSED_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_ALL_PASSED_H

#include "conceptrodon/concepts/typelivore/all_passed.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAllPassed {




/******************************************************************************************************/
template<auto Arg>
struct AreGreaterThan
{
    constexpr bool operator()(auto para)
    { return para > Arg; }
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AllPassed<AreGreaterThan<0>, 1, 2, 3>);
static_assert(! AllPassed<AreGreaterThan<0>, 0, 2, 3>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AllPassed<AreGreaterThan<0>, Args...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AllPassed<AreGreaterThan<1>, Args...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AllPassed<AreGreaterThan<0>, Args...>
&& AllPassed<AreGreaterThan<1>, Args...>
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
= AllPassed<AreGreaterThan<1>, Args...>;


template<auto...Args>
requires AllPassed<AreGreaterThan<0>, Args...>
&& AllPassed<AreGreaterThan<1>, Args...>
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
= (...&&AreGreaterThan<1>{}(Args));

template<auto...Args>
requires AllPassed<AreGreaterThan<0>, Args...>
&& AllPassed<AreGreaterThan<1>, Args...>
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
= (...&&AreGreaterThan<2>{}(Args));

template<auto...Args>
concept GreaterThanTwoB
= (...&&AreGreaterThan<2>{}(Args));

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
= AllPassed<AreGreaterThan<2>, Args...>;

template<auto...Args>
concept GreaterThanTwoD
= AllPassed<AreGreaterThan<2>, Args...>;

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