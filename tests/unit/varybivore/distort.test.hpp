// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DISTORT_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DISTORT_H

#include "conceptrodon/varybivore/concepts/distort.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestDistort {




/******************************************************************************************************/
template<auto Arg>
constexpr bool areNoGreaterThan(int para)
{ return para <= Arg; }

template<auto >
struct Tester {};

template<auto Arg>
requires Distort<areNoGreaterThan<0>, Arg>
struct Tester<Arg>
{
    static constexpr int value {0};
};

template<auto Arg>
requires Distort<areNoGreaterThan<1>, Arg>
struct Tester<Arg>
{
    static constexpr int value {-1};
};

template<auto Arg>
requires Distort<areNoGreaterThan<0>, Arg>
&& Distort<areNoGreaterThan<1>, Arg>
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
= Distort<areNoGreaterThan<1>, Arg>;

template<auto Arg>
concept Truth = true;

template<auto Arg>
requires Distort<areNoGreaterThan<0>, Arg>
&& Distort<areNoGreaterThan<1>, Arg>
&& GreaterThanOneA<Arg>
struct Tester<Arg>
{
    static constexpr double value {1.1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1>::value == 0);
static_assert(Tester<2>::value == 1);
// static_assert(Tester<3>::value == 1.1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto Arg>
concept GreaterThanOneB
= not areNoGreaterThan<1>(Arg);

template<auto Arg>
requires Distort<areNoGreaterThan<0>, Arg>
&& Distort<areNoGreaterThan<1>, Arg>
&& GreaterThanOneB<Arg>
struct Tester<Arg>
{
    static constexpr double value {1.2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1>::value == 0);
static_assert(Tester<2>::value == 1);
static_assert(Tester<3>::value == 1.2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto Arg>
concept GreaterThanTwoA
= not areNoGreaterThan<2>(Arg);

template<auto Arg>
concept GreaterThanTwoB
= not areNoGreaterThan<2>(Arg);

template<auto >
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
= Distort<areNoGreaterThan<2>, Arg>;

template<auto Arg>
concept GreaterThanTwoD
= Distort<areNoGreaterThan<2>, Arg>;

template<auto >
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