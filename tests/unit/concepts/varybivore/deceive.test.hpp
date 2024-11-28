// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DECEIVE_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DECEIVE_H

#include "conceptrodon/monotony.hpp"
#include "conceptrodon/varybivore/concepts/deceive.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestDeceive {




/******************************************************************************************************/
template<auto Arg>
constexpr bool areNoGreaterThan(auto...para)
{ return (...&&(para <= Arg)); }

template<auto...>
struct Tester {};

template<auto...Args>
requires Deceive<areNoGreaterThan<0, decltype(Args)...>, Monotony<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires Deceive<areNoGreaterThan<1, decltype(Args)...>, Monotony<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires Deceive<areNoGreaterThan<0, decltype(Args)...>, Monotony<Args>...>
&& Deceive<areNoGreaterThan<1, decltype(Args)...>, Monotony<Args>...>
struct Tester<Args...>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1>::value == 0);
static_assert(Tester<2>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanOneA
= Deceive<areNoGreaterThan<1, decltype(Args)...>, Monotony<Args>...>;


template<auto...Args>
requires Deceive<areNoGreaterThan<0, decltype(Args)...>, Monotony<Args>...>
&& Deceive<areNoGreaterThan<1, decltype(Args)...>, Monotony<Args>...>
&& GreaterThanOneA<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<0.9>::value == 0);
static_assert(Tester<2>::value == 1);
// static_assert(Tester<3>::value == 1.1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanOneB
= not areNoGreaterThan<1>(Args...);

template<auto...Args>
requires Deceive<areNoGreaterThan<0, decltype(Args)...>, Monotony<Args>...>
&& Deceive<areNoGreaterThan<1, decltype(Args)...>, Monotony<Args>...>
&& GreaterThanOneB<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<0.8>::value == 0);
static_assert(Tester<2>::value == 1);
static_assert(Tester<3>::value == 1.2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept GreaterThanTwoA
= not areNoGreaterThan<2>(Args...);

template<auto...Args>
concept GreaterThanTwoB
= not areNoGreaterThan<2>(Args...);

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
= Deceive<areNoGreaterThan<2, decltype(Args)...>, Monotony<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= Deceive<areNoGreaterThan<2, decltype(Args)...>, Monotony<Args>...>;

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

// static_assert(TesterC<3>::value == 2);
/******************************************************************************************************/




}}}}

#endif