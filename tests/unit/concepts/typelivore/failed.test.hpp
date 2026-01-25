// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_FAILED_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_FAILED_H

#include "conceptrodon/concepts/typelivore/failed.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestFailed {




/******************************************************************************************************/
template<auto Arg>
struct AreNoGreaterThan
{
    constexpr bool operator()(auto para)
    { return para <= Arg; }
};

template<auto>
struct Tester {};

template<auto Arg>
requires Failed<AreNoGreaterThan<0>, Arg>
struct Tester<Arg>
{
    static constexpr int value {0};
};

template<auto Arg>
requires Failed<AreNoGreaterThan<1>, Arg>
struct Tester<Arg>
{
    static constexpr int value {-1};
};

template<auto Arg>
requires Failed<AreNoGreaterThan<0>, Arg>
&& Failed<AreNoGreaterThan<1>, Arg>
struct Tester<Arg>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1>::value == 0);
static_assert(Tester<2>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto Arg>
concept GreaterThanOneA
= Failed<AreNoGreaterThan<1>, Arg>;

template<auto Arg>
concept Truth = true;

template<auto Arg>
requires Failed<AreNoGreaterThan<0>, Arg>
&& Failed<AreNoGreaterThan<1>, Arg>
&& GreaterThanOneA<Arg>
struct Tester<Arg>
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
template<auto Arg>
concept GreaterThanOneB
= not AreNoGreaterThan<1>{}(Arg);

template<auto Arg>
requires Failed<AreNoGreaterThan<0>, Arg>
&& Failed<AreNoGreaterThan<1>, Arg>
&& GreaterThanOneB<Arg>
struct Tester<Arg>
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
template<auto Arg>
concept GreaterThanTwoA
= not AreNoGreaterThan<2>{}(Arg);

template<auto Arg>
concept GreaterThanTwoB
= not AreNoGreaterThan<2>{}(Arg);

template<auto>
struct TesterB;

template<auto Arg>
requires GreaterThanTwoA<Arg>
struct TesterB<Arg>
{
    static constexpr int value {-2};
};

template<auto Arg>
requires GreaterThanTwoA<Arg>
&& GreaterThanTwoB<Arg>
struct TesterB<Arg>
{
    static constexpr int value {2};
};

static_assert(TesterB<3>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto Arg>
concept GreaterThanTwoC
= Failed<AreNoGreaterThan<2>, Arg>;

template<auto Arg>
concept GreaterThanTwoD
= Failed<AreNoGreaterThan<2>, Arg>;

template<auto>
struct TesterC;

template<auto Arg>
requires GreaterThanTwoC<Arg>
struct TesterC<Arg>
{
    static constexpr int value {-2};
};

template<auto Arg>
requires GreaterThanTwoC<Arg>
&& GreaterThanTwoD<Arg>
struct TesterC<Arg>
{
    static constexpr int value {2};
};

// static_assert(TesterC<3>::value == 2);
/******************************************************************************************************/




}}}}

#endif