// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_DECEIVE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ALL_DECEIVE_H

#include "conceptrodon/vay.hpp"
#include "conceptrodon/typelivore/concepts/all_deceive.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAllDeceive {




/******************************************************************************************************/
template<auto Arg>
struct AreNoGreaterThan
{
    constexpr bool operator()(auto para)
    { return para <= Arg; }
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AllDeceive<AreNoGreaterThan<0>, Vay<1>, Vay<2>, Vay<3>>);
static_assert(! AllDeceive<AreNoGreaterThan<0>, Vay<0>, Vay<2>, Vay<3>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto... Args>
requires AllDeceive<AreNoGreaterThan<0>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto... Args>
requires AllDeceive<AreNoGreaterThan<1>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto... Args>
requires AllDeceive<AreNoGreaterThan<0>, Vay<Args>...>
&& AllDeceive<AreNoGreaterThan<1>, Vay<Args>...>
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
template<auto... Args>
concept GreaterThanOneA
= AllDeceive<AreNoGreaterThan<1>, Vay<Args>...>;

template<auto... Args>
concept Truth = true;

template<auto... Args>
requires AllDeceive<AreNoGreaterThan<0>, Vay<Args>...>
&& AllDeceive<AreNoGreaterThan<1>, Vay<Args>...>
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
template<auto... Args>
concept GreaterThanOneB
= (...&&(not AreNoGreaterThan<1>{}(Args)));

template<auto... Args>
requires AllDeceive<AreNoGreaterThan<0>, Vay<Args>...>
&& AllDeceive<AreNoGreaterThan<1>, Vay<Args>...>
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
template<auto... Args>
concept GreaterThanTwoA
= (...&&(not AreNoGreaterThan<2>{}(Args)));

template<auto... Args>
concept GreaterThanTwoB
= (...&&(not AreNoGreaterThan<2>{}(Args)));

template<auto...>
struct TesterB;

template<auto... Args>
requires GreaterThanTwoA<Args...>
struct TesterB<Args...>
{
    static constexpr int value {-2};
};

template<auto... Args>
requires GreaterThanTwoA<Args...>
&& GreaterThanTwoB<Args...>
struct TesterB<Args...>
{
    static constexpr int value {2};
};

static_assert(TesterB<3, 4, 5>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto... Args>
concept GreaterThanTwoC
= AllDeceive<AreNoGreaterThan<2>, Vay<Args>...>;

template<auto... Args>
concept GreaterThanTwoD
= AllDeceive<AreNoGreaterThan<2>, Vay<Args>...>;

template<auto...>
struct TesterC;

template<auto... Args>
requires GreaterThanTwoC<Args...>
struct TesterC<Args...>
{
    static constexpr int value {-2};
};

template<auto... Args>
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