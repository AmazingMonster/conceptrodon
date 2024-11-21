// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_DECEIVE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ANY_DECEIVE_H

#include "conceptrodon/monotony.hpp"
#include "conceptrodon/typelivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAnyDeceive {




/******************************************************************************************************/
template<auto Arg>
struct AreNoGreaterThan
{
    constexpr bool operator()(auto para)
    { return para <= Arg; }
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AnyDeceive<AreNoGreaterThan<0>, Monotony<1>, Monotony<2>, Monotony<3>>);
static_assert(AnyDeceive<AreNoGreaterThan<0>, Monotony<1>, Monotony<-2>, Monotony<-3>>);
static_assert(! AnyDeceive<AreNoGreaterThan<0>, Monotony<0>, Monotony<-1>, Monotony<-2>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto... Args>
requires AnyDeceive<AreNoGreaterThan<0>, Monotony<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto... Args>
requires AnyDeceive<AreNoGreaterThan<1>, Monotony<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto... Args>
requires AnyDeceive<AreNoGreaterThan<0>, Monotony<Args>...>
&& AnyDeceive<AreNoGreaterThan<1>, Monotony<Args>...>
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
= AnyDeceive<AreNoGreaterThan<1>, Monotony<Args>...>;

template<auto...Args>
requires AnyDeceive<AreNoGreaterThan<0>, Monotony<Args>...>
&& AnyDeceive<AreNoGreaterThan<1>, Monotony<Args>...>
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
= (...||(not AreNoGreaterThan<1>{}(Args)));

template<auto...Args>
requires AnyDeceive<AreNoGreaterThan<0>, Monotony<Args>...>
&& AnyDeceive<AreNoGreaterThan<1>, Monotony<Args>...>
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
= (...||(not AreNoGreaterThan<2>{}(Args)));

template<auto...Args>
concept GreaterThanTwoB
= (...||(not AreNoGreaterThan<2>{}(Args)));

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
= AnyDeceive<AreNoGreaterThan<2>, Monotony<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= AnyDeceive<AreNoGreaterThan<2>, Monotony<Args>...>;

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

// static_assert(TesterC<3, -4, -5>::value == 2);
/******************************************************************************************************/




}}}}

#endif