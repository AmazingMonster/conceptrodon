// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_DECEIVE_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_DECEIVE_H

#include "conceptrodon/pagelivore/concepts/deceive.hpp"
#include "conceptrodon/varybivore/are_no_greater_than.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestDeceive {




/******************************************************************************************************/
template<auto>
struct Tester {};

template<auto Arg>
requires Deceive<Varybivore::AreNoGreaterThan<0>::Page, Monotony<Arg>>
struct Tester<Arg>
{
    static constexpr int value {0};
};

template<auto Arg>
requires Deceive<Varybivore::AreNoGreaterThan<1>::Page, Monotony<Arg>>
struct Tester<Arg>
{
    static constexpr int value {-1};
};

template<auto Arg>
requires Deceive<Varybivore::AreNoGreaterThan<0>::Page, Monotony<Arg>>
&& Deceive<Varybivore::AreNoGreaterThan<1>::Page, Monotony<Arg>>
struct Tester<Arg>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<1>::value == 0);
static_assert(Tester<2>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto Arg>
concept GreaterThanOneA
= Deceive<Varybivore::AreNoGreaterThan<1>::Page, Monotony<Arg>>;

template<auto Arg>
concept Truth = true;

template<auto Arg>
requires Deceive<Varybivore::AreNoGreaterThan<0>::Page, Monotony<Arg>>
&& Deceive<Varybivore::AreNoGreaterThan<1>::Page, Monotony<Arg>>
&& GreaterThanOneA<Arg>
struct Tester<Arg>
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
template<auto Arg>
concept GreaterThanOneB
= not Varybivore::AreNoGreaterThan<1>::Page<Arg>::value;

template<auto Arg>
requires Deceive<Varybivore::AreNoGreaterThan<0>::Page, Monotony<Arg>>
&& Deceive<Varybivore::AreNoGreaterThan<1>::Page, Monotony<Arg>>
&& GreaterThanOneB<Arg>
struct Tester<Arg>
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
template<auto Arg>
concept GreaterThanTwoA
= not Varybivore::AreNoGreaterThan<2>::Page<Arg>::value;

template<auto Arg>
concept GreaterThanTwoB
= not Varybivore::AreNoGreaterThan<2>::Page<Arg>::value;

template<auto>
struct TesterB;

template<auto Arg>
requires GreaterThanTwoA<Arg>
struct TesterB<Arg>
{
    static constexpr int value {-2};
};

template<auto Arg>
requires GreaterThanTwoA<Arg>
&& GreaterThanTwoB<Arg>
struct TesterB<Arg>
{
    static constexpr int value {2};
};

static_assert(TesterB<3>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto Arg>
concept GreaterThanTwoC
= Deceive<Varybivore::AreNoGreaterThan<2>::Page, Monotony<Arg>>;

template<auto Arg>
concept GreaterThanTwoD
= Deceive<Varybivore::AreNoGreaterThan<2>::Page, Monotony<Arg>>;

template<auto>
struct TesterC;

template<auto Arg>
requires GreaterThanTwoC<Arg>
struct TesterC<Arg>
{
    static constexpr int value {-2};
};

template<auto Arg>
requires GreaterThanTwoC<Arg>
&& GreaterThanTwoD<Arg>
struct TesterC<Arg>
{
    static constexpr int value {2};
};

// static_assert(TesterC<3>::value == 2);
/******************************************************************************************************/




}}}}

#endif