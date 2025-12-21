// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ALL_FALSIFY_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ALL_FALSIFY_H

#include "conceptrodon/metafunctions/pagelivore/concepts/all_falsify.hpp"
#include "conceptrodon/metafunctions/varybivore/are_no_greater_than.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestAllFalsify {




/******************************************************************************************************/
static_assert(AllFalsify<Varybivore::AreNoGreaterThan<0>::Page, 1, 2, 3>);
static_assert(! AllFalsify<Varybivore::AreNoGreaterThan<0>::Page, 1, -2, -3>);
static_assert(! AllFalsify<Varybivore::AreNoGreaterThan<0>::Page, 0, -1, -2>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AllFalsify<Varybivore::AreNoGreaterThan<0>::Page, Args...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AllFalsify<Varybivore::AreNoGreaterThan<1>::Page, Args...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AllFalsify<Varybivore::AreNoGreaterThan<0>::Page, Args...>
&& AllFalsify<Varybivore::AreNoGreaterThan<1>::Page, Args...>
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
= AllFalsify<Varybivore::AreNoGreaterThan<1>::Page, Args...>;


template<auto...Args>
requires AllFalsify<Varybivore::AreNoGreaterThan<0>::Page, Args...>
&& AllFalsify<Varybivore::AreNoGreaterThan<1>::Page, Args...>
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
= (...&&(not Varybivore::AreNoGreaterThan<1>::Page<Args>::value));

template<auto...Args>
requires AllFalsify<Varybivore::AreNoGreaterThan<0>::Page, Args...>
&& AllFalsify<Varybivore::AreNoGreaterThan<1>::Page, Args...>
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
= (...&&(not Varybivore::AreNoGreaterThan<2>::Page<Args>::value));

template<auto...Args>
concept GreaterThanTwoB
= (...&&(not Varybivore::AreNoGreaterThan<2>::Page<Args>::value));

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
= AllFalsify<Varybivore::AreNoGreaterThan<2>::Page, Args...>;

template<auto...Args>
concept GreaterThanTwoD
= AllFalsify<Varybivore::AreNoGreaterThan<2>::Page, Args...>;

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