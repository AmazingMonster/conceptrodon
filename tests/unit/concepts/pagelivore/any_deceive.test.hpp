// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ANY_DECEIVE_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ANY_DECEIVE_H

#include "conceptrodon/utilities/vay.hpp"
#include "conceptrodon/pagelivore/concepts/any_deceive.hpp"
#include "conceptrodon/varybivore/are_no_greater_than.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestAnyDeceive {




/******************************************************************************************************/
static_assert(AnyDeceive<Varybivore::AreNoGreaterThan<0>::Page, Vay<1>, Vay<2>, Vay<3>>);
static_assert(AnyDeceive<Varybivore::AreNoGreaterThan<0>::Page, Vay<1>, Vay<-2>, Vay<-3>>);
static_assert(! AnyDeceive<Varybivore::AreNoGreaterThan<0>::Page, Vay<0>, Vay<-1>, Vay<-2>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AnyDeceive<Varybivore::AreNoGreaterThan<0>::Page, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AnyDeceive<Varybivore::AreNoGreaterThan<1>::Page, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AnyDeceive<Varybivore::AreNoGreaterThan<0>::Page, Vay<Args>...>
&& AnyDeceive<Varybivore::AreNoGreaterThan<1>::Page, Vay<Args>...>
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
= AnyDeceive<Varybivore::AreNoGreaterThan<1>::Page, Vay<Args>...>;


template<auto...Args>
requires AnyDeceive<Varybivore::AreNoGreaterThan<0>::Page, Vay<Args>...>
&& AnyDeceive<Varybivore::AreNoGreaterThan<1>::Page, Vay<Args>...>
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
= (...||(not Varybivore::AreNoGreaterThan<1>::Page<Args>::value));

template<auto...Args>
requires AnyDeceive<Varybivore::AreNoGreaterThan<0>::Page, Vay<Args>...>
&& AnyDeceive<Varybivore::AreNoGreaterThan<1>::Page, Vay<Args>...>
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
= (...||(not Varybivore::AreNoGreaterThan<2>::Page<Args>::value));

template<auto...Args>
concept GreaterThanTwoB
= (...||(not Varybivore::AreNoGreaterThan<2>::Page<Args>::value));

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
= AnyDeceive<Varybivore::AreNoGreaterThan<2>::Page, Vay<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= AnyDeceive<Varybivore::AreNoGreaterThan<2>::Page, Vay<Args>...>;

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