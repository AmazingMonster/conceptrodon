// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CONFESS_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CONFESS_H

#include "conceptrodon/vay.hpp"
#include "conceptrodon/varybivore/concepts/confess.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestConfess {




/******************************************************************************************************/
template<auto Arg>
constexpr bool areGreaterThan(auto...para)
{ return (...&&(para > Arg)); }

template<auto...>
struct Tester {};

template<auto...Args>
requires Confess<areGreaterThan<0, decltype(Args)...>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires Confess<areGreaterThan<1, decltype(Args)...>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires Confess<areGreaterThan<0, decltype(Args)...>, Vay<Args>...>
&& Confess<areGreaterThan<1, decltype(Args)...>, Vay<Args>...>
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
= Confess<areGreaterThan<1, decltype(Args)...>, Vay<Args>...>;

template<auto...Args>
requires Confess<areGreaterThan<0, decltype(Args)...>, Vay<Args>...>
&& Confess<areGreaterThan<1, decltype(Args)...>, Vay<Args>...>
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
= areGreaterThan<1>(Args...);

template<auto...Args>
requires Confess<areGreaterThan<0, decltype(Args)...>, Vay<Args>...>
&& Confess<areGreaterThan<1, decltype(Args)...>, Vay<Args>...>
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
= areGreaterThan<2>(Args...);

template<auto...Args>
concept GreaterThanTwoB
= areGreaterThan<2>(Args...);

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
= Confess<areGreaterThan<2, decltype(Args)...>, Vay<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= Confess<areGreaterThan<2, decltype(Args)...>, Vay<Args>...>;

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