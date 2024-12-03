// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ALL_CONFESS_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ALL_CONFESS_H

#include "conceptrodon/vay.hpp"
#include "conceptrodon/varybivore/concepts/all_confess.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAllConfess {




/******************************************************************************************************/
template<auto Arg>
constexpr bool areGreaterThan(int para)
{ return para > Arg; }
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AllConfess<areGreaterThan<0>, Vay<1>, Vay<2>, Vay<3>>);
static_assert(! AllConfess<areGreaterThan<0>, Vay<0>, Vay<2>, Vay<3>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AllConfess<areGreaterThan<0>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AllConfess<areGreaterThan<1>, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AllConfess<areGreaterThan<0>, Vay<Args>...>
&& AllConfess<areGreaterThan<1>, Vay<Args>...>
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
= AllConfess<areGreaterThan<1>, Vay<Args>...>;

template<auto...Args>
requires AllConfess<areGreaterThan<0>, Vay<Args>...>
&& AllConfess<areGreaterThan<1>, Vay<Args>...>
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
= (...&&(areGreaterThan<1>(Args)));

template<auto...Args>
requires AllConfess<areGreaterThan<0>, Vay<Args>...>
&& AllConfess<areGreaterThan<1>, Vay<Args>...>
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
= (...&&(areGreaterThan<2>(Args)));

template<auto...Args>
concept GreaterThanTwoB
= (...&&(areGreaterThan<2>(Args)));

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
= AllConfess<areGreaterThan<2>, Vay<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= AllConfess<areGreaterThan<2>, Vay<Args>...>;

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