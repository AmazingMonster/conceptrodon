// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ALL_CONFESS_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_ALL_CONFESS_H

#include "conceptrodon/monotony.hpp"
#include "conceptrodon/pagelivore/concepts/all_confess.hpp"
#include "conceptrodon/varybivore/are_greater_than.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestAllConfess {




/******************************************************************************************************/
static_assert(AllConfess<Varybivore::AreGreaterThan<0>::Page, Monotony<1>, Monotony<2>, Monotony<3>>);
static_assert(! AllConfess<Varybivore::AreGreaterThan<0>::Page, Monotony<1>, Monotony<-2>, Monotony<-3>>);
static_assert(! AllConfess<Varybivore::AreGreaterThan<0>::Page, Monotony<0>, Monotony<-1>, Monotony<-2>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AllConfess<Varybivore::AreGreaterThan<0>::Page, Monotony<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AllConfess<Varybivore::AreGreaterThan<1>::Page, Monotony<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AllConfess<Varybivore::AreGreaterThan<0>::Page, Monotony<Args>...>
&& AllConfess<Varybivore::AreGreaterThan<1>::Page, Monotony<Args>...>
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
= AllConfess<Varybivore::AreGreaterThan<1>::Page, Monotony<Args>...>;


template<auto...Args>
requires AllConfess<Varybivore::AreGreaterThan<0>::Page, Monotony<Args>...>
&& AllConfess<Varybivore::AreGreaterThan<1>::Page, Monotony<Args>...>
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
= (...&&(Varybivore::AreGreaterThan<1>::Page<Args>::value));

template<auto...Args>
requires AllConfess<Varybivore::AreGreaterThan<0>::Page, Monotony<Args>...>
&& AllConfess<Varybivore::AreGreaterThan<1>::Page, Monotony<Args>...>
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
= (...&&(Varybivore::AreGreaterThan<1>::Page<Args>::value));

template<auto...Args>
concept GreaterThanTwoB
= (...&&(Varybivore::AreGreaterThan<1>::Page<Args>::value));

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
= AllConfess<Varybivore::AreGreaterThan<2>::Page, Monotony<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= AllConfess<Varybivore::AreGreaterThan<2>::Page, Monotony<Args>...>;

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