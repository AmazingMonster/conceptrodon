// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CLARIFY_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CLARIFY_H

#include "conceptrodon/varybivore/concepts/clarify.hpp"
#include "conceptrodon/varybivore/are_greater_than.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestClarify {

/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires Clarify<AreGreaterThan<0>::Page, Args...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires Clarify<AreGreaterThan<1>::Page, Args...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires Clarify<AreGreaterThan<0>::Page, Args...>
&& Clarify<AreGreaterThan<1>::Page, Args...>
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
= Clarify<AreGreaterThan<1>::Page, Args...>;

template<auto...Args>
concept Truth = true;

template<auto...Args>
requires Clarify<AreGreaterThan<0>::Page, Args...>
&& Clarify<AreGreaterThan<1>::Page, Args...>
&& GreaterThanOneA<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 2, 3>::value == 0);
static_assert(Tester<2, 3, 4>::value == 1);
// static_assert(Tester<3, 4, 5>::value == 1.1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanOneB
= AreGreaterThan<1>::Page<Args...>::value;

template<auto...Args>
requires Clarify<AreGreaterThan<0>::Page, Args...>
&& Clarify<AreGreaterThan<1>::Page, Args...>
&& GreaterThanOneB<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1, 2, 3>::value == 0);
static_assert(Tester<2, 3, 4>::value == 1);
static_assert(Tester<3, 4, 5>::value == 1.2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanTwoA
= AreGreaterThan<2>::Page<Args...>::value;

template<auto...Args>
concept GreaterThanTwoB
= AreGreaterThan<2>::Page<Args...>::value;

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
= Clarify<AreGreaterThan<2>::Page, Args...>;

template<auto...Args>
concept GreaterThanTwoD
= Clarify<AreGreaterThan<2>::Page, Args...>;

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