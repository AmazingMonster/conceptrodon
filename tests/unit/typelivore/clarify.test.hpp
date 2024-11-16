// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_CLARIFY_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_CLARIFY_H

#include "conceptrodon/typelivore/concepts/clarify.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestClarify {

/******************************************************************************************************/
template<auto Target>
struct AreGreaterThan
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        { (...&&(Target < Elements::value)) };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<typename...>
struct Tester {};

template<typename...Args>
requires Clarify<AreGreaterThan<0>::Mold, Args...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<typename...Args>
requires Clarify<AreGreaterThan<1>::Mold, Args...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<typename...Args>
requires Clarify<AreGreaterThan<0>::Mold, Args...>
&& Clarify<AreGreaterThan<1>::Mold, Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<1>, Monotony<2>, Monotony<3>>::value == 0);
static_assert(Tester<Monotony<2>, Monotony<3>, Monotony<4>>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
concept GreaterThanOneA
= Clarify<AreGreaterThan<1>::Mold, Args...>;

template<typename...Args>
concept Truth = true;

template<typename...Args>
requires Clarify<AreGreaterThan<0>::Mold, Args...>
&& Clarify<AreGreaterThan<1>::Mold, Args...>
&& GreaterThanOneA<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<1>, Monotony<2>, Monotony<3>>::value == 0);
static_assert(Tester<Monotony<2>, Monotony<3>, Monotony<4>>::value == 1);
// static_assert(Tester<Monotony<3>, Monotony<4>, Monotony<5>>::value == 1.1);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
concept GreaterThanOneB
= AreGreaterThan<1>::Mold<Args...>::value;

template<typename...Args>
requires Clarify<AreGreaterThan<0>::Mold, Args...>
&& Clarify<AreGreaterThan<1>::Mold, Args...>
&& GreaterThanOneB<Args...>
struct Tester<Args...>
{
    static constexpr double value {1.2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Monotony<1>, Monotony<2>, Monotony<3>>::value == 0);
static_assert(Tester<Monotony<2>, Monotony<3>, Monotony<4>>::value == 1);
static_assert(Tester<Monotony<3>, Monotony<4>, Monotony<5>>::value == 1.2);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
concept GreaterThanTwoA
= AreGreaterThan<2>::Mold<Args...>::value;

template<typename...Args>
concept GreaterThanTwoB
= AreGreaterThan<2>::Mold<Args...>::value;

template<typename...>
struct TesterB;

template<typename...Args>
requires GreaterThanTwoA<Args...>
struct TesterB<Args...>
{
    static constexpr int value {-2};
};

template<typename...Args>
requires GreaterThanTwoA<Args...>
&& GreaterThanTwoB<Args...>
struct TesterB<Args...>
{
    static constexpr int value {2};
};

static_assert(TesterB<Monotony<3>, Monotony<4>, Monotony<5>>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
concept GreaterThanTwoC
= Clarify<AreGreaterThan<2>::Mold, Args...>;

template<typename...Args>
concept GreaterThanTwoD
= Clarify<AreGreaterThan<2>::Mold, Args...>;

template<typename...>
struct TesterC;

template<typename...Args>
requires GreaterThanTwoC<Args...>
struct TesterC<Args...>
{
    static constexpr int value {-2};
};

template<typename...Args>
requires GreaterThanTwoC<Args...>
&& GreaterThanTwoD<Args...>
struct TesterC<Args...>
{
    static constexpr int value {2};
};

// static_assert(TesterC<Monotony<3>, Monotony<4>, Monotony<5>>::value == 2);
/******************************************************************************************************/




}}}}

#endif