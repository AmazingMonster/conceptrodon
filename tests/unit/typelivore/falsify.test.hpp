// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_FALSIFY_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_FALSIFY_H

#include "conceptrodon/monotony.hpp"
#include "conceptrodon/typelivore/concepts/falsify.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestFalsify {

/******************************************************************************************************/
template<auto Target>
struct AreNoGreaterThan
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        { (...&&(Target >= Elements::value)) };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<typename>
struct Tester {};

template<typename Arg>
requires Falsify<AreNoGreaterThan<0>::Mold, Arg>
struct Tester<Arg>
{
    static constexpr int value {0};
};

template<typename Arg>
requires Falsify<AreNoGreaterThan<1>::Mold, Arg>
struct Tester<Arg>
{
    static constexpr int value {-1};
};

template<typename Arg>
requires Falsify<AreNoGreaterThan<0>::Mold, Arg>
&& Falsify<AreNoGreaterThan<1>::Mold, Arg>
struct Tester<Arg>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<1>>::value == 0);
static_assert(Tester<Monotony<2>>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename Arg>
concept GreaterThanOneA
= Falsify<AreNoGreaterThan<1>::Mold, Arg>;

template<typename Arg>
concept Truth = true;

template<typename Arg>
requires Falsify<AreNoGreaterThan<0>::Mold, Arg>
&& Falsify<AreNoGreaterThan<1>::Mold, Arg>
&& GreaterThanOneA<Arg>
struct Tester<Arg>
{
    static constexpr double value {1.1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<1>>::value == 0);
static_assert(Tester<Monotony<2>>::value == 1);
// static_assert(Tester<Monotony<3>>::value == 1.1);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename Arg>
concept GreaterThanOneB
= not AreNoGreaterThan<1>::Mold<Arg>::value;

template<typename Arg>
requires Falsify<AreNoGreaterThan<0>::Mold, Arg>
&& Falsify<AreNoGreaterThan<1>::Mold, Arg>
&& GreaterThanOneB<Arg>
struct Tester<Arg>
{
    static constexpr double value {1.2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<1>>::value == 0);
static_assert(Tester<Monotony<2>>::value == 1);
static_assert(Tester<Monotony<3>>::value == 1.2);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename Arg>
concept GreaterThanTwoA
= not AreNoGreaterThan<2>::Mold<Arg>::value;

template<typename Arg>
concept GreaterThanTwoB
= not AreNoGreaterThan<2>::Mold<Arg>::value;

template<typename>
struct TesterB;

template<typename Arg>
requires GreaterThanTwoA<Arg>
struct TesterB<Arg>
{
    static constexpr int value {-2};
};

template<typename Arg>
requires GreaterThanTwoA<Arg>
&& GreaterThanTwoB<Arg>
struct TesterB<Arg>
{
    static constexpr int value {2};
};

static_assert(TesterB<Monotony<3>>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename Arg>
concept GreaterThanTwoC
= Falsify<AreNoGreaterThan<2>::Mold, Arg>;

template<typename Arg>
concept GreaterThanTwoD
= Falsify<AreNoGreaterThan<2>::Mold, Arg>;

template<typename>
struct TesterC;

template<typename Arg>
requires GreaterThanTwoC<Arg>
struct TesterC<Arg>
{
    static constexpr int value {-2};
};

template<typename Arg>
requires GreaterThanTwoC<Arg>
&& GreaterThanTwoD<Arg>
struct TesterC<Arg>
{
    static constexpr int value {2};
};

// static_assert(TesterC<Monotony<3>>::value == 2);
/******************************************************************************************************/




}}}}

#endif