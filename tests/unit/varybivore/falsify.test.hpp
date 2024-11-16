// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_FALSIFY_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_FALSIFY_H

#include "conceptrodon/varybivore/concepts/falsify.hpp"
#include "conceptrodon/varybivore/are_no_greater_than.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestFalsify {




/******************************************************************************************************/
template<auto >
struct Tester {};

template<auto Arg>
requires Falsify<AreNoGreaterThan<0>::Page, Arg>
struct Tester<Arg>
{
    static constexpr int value {0};
};

template<auto Arg>
requires Falsify<AreNoGreaterThan<1>::Page, Arg>
struct Tester<Arg>
{
    static constexpr int value {-1};
};

template<auto Arg>
requires Falsify<AreNoGreaterThan<0>::Page, Arg>
&& Falsify<AreNoGreaterThan<1>::Page, Arg>
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
= Falsify<AreNoGreaterThan<1>::Page, Arg>;

template<auto Arg>
concept Truth = true;

template<auto Arg>
requires Falsify<AreNoGreaterThan<0>::Page, Arg>
&& Falsify<AreNoGreaterThan<1>::Page, Arg>
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
= not AreNoGreaterThan<1>::Page<Arg>::value;

template<auto Arg>
requires Falsify<AreNoGreaterThan<0>::Page, Arg>
&& Falsify<AreNoGreaterThan<1>::Page, Arg>
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
= not AreNoGreaterThan<2>::Page<Arg>::value;

template<auto Arg>
concept GreaterThanTwoB
= not AreNoGreaterThan<2>::Page<Arg>::value;

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
= Falsify<AreNoGreaterThan<2>::Page, Arg>;

template<auto Arg>
concept GreaterThanTwoD
= Falsify<AreNoGreaterThan<2>::Page, Arg>;

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