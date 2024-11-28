// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ANY_CLARIFY_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ANY_CLARIFY_H

#include "conceptrodon/pagelivore/concepts/any_clarify.hpp"
#include "conceptrodon/varybivore/are_greater_than.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestAnyClarify {




/******************************************************************************************************/
static_assert(AnyClarify<Varybivore::AreGreaterThan<0>::Page, 1, 2, 3>);
static_assert(AnyClarify<Varybivore::AreGreaterThan<0>::Page, 1, -2, -3>);
static_assert(! AnyClarify<Varybivore::AreGreaterThan<0>::Page, 0, -1, -2>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AnyClarify<Varybivore::AreGreaterThan<0>::Page, Args...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AnyClarify<Varybivore::AreGreaterThan<1>::Page, Args...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AnyClarify<Varybivore::AreGreaterThan<0>::Page, Args...>
&& AnyClarify<Varybivore::AreGreaterThan<1>::Page, Args...>
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
= AnyClarify<Varybivore::AreGreaterThan<1>::Page, Args...>;


template<auto...Args>
requires AnyClarify<Varybivore::AreGreaterThan<0>::Page, Args...>
&& AnyClarify<Varybivore::AreGreaterThan<1>::Page, Args...>
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
= (...||(Varybivore::AreGreaterThan<1>::Page<Args>::value));

template<auto...Args>
requires AnyClarify<Varybivore::AreGreaterThan<0>::Page, Args...>
&& AnyClarify<Varybivore::AreGreaterThan<1>::Page, Args...>
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
= (...||(Varybivore::AreGreaterThan<1>::Page<Args>::value));

template<auto...Args>
concept GreaterThanTwoB
= (...||(Varybivore::AreGreaterThan<1>::Page<Args>::value));

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

static_assert(TesterB<3, -4, -5>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanTwoC
= AnyClarify<Varybivore::AreGreaterThan<2>::Page, Args...>;

template<auto...Args>
concept GreaterThanTwoD
= AnyClarify<Varybivore::AreGreaterThan<2>::Page, Args...>;

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

// static_assert(TesterC<3, -4, -5>::value == 2);
/******************************************************************************************************/




}}}}

#endif