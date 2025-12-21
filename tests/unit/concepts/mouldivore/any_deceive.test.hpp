// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_ANY_DECEIVE_H
#define CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_ANY_DECEIVE_H

#include "conceptrodon/utilities/vay.hpp"
#include "conceptrodon/concepts/mouldivore/any_deceive.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestAnyDeceive {

/******************************************************************************************************/
template<auto Target>
struct AreNoGreaterThan
{
    template<typename Element>
    struct ProtoMold
    {
        static constexpr bool value
        { Target >= Element::value };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AnyDeceive<AreNoGreaterThan<0>::Mold, Vay<1>, Vay<2>, Vay<3>>);
static_assert(AnyDeceive<AreNoGreaterThan<0>::Mold, Vay<1>, Vay<-2>, Vay<-3>>);
static_assert(! AnyDeceive<AreNoGreaterThan<0>::Mold, Vay<0>, Vay<-1>, Vay<-2>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AnyDeceive<AreNoGreaterThan<0>::Mold, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AnyDeceive<AreNoGreaterThan<1>::Mold, Vay<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AnyDeceive<AreNoGreaterThan<0>::Mold, Vay<Args>...>
&& AnyDeceive<AreNoGreaterThan<1>::Mold, Vay<Args>...>
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
= AnyDeceive<AreNoGreaterThan<1>::Mold, Vay<Args>...>;

template<auto...Arg>
concept Truth = true;

template<auto...Args>
requires AnyDeceive<AreNoGreaterThan<0>::Mold, Vay<Args>...>
&& AnyDeceive<AreNoGreaterThan<1>::Mold, Vay<Args>...>
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
= (...||(not AreNoGreaterThan<1>::Mold<Vay<Args>>::value));

template<auto...Args>
requires AnyDeceive<AreNoGreaterThan<0>::Mold, Vay<Args>...>
&& AnyDeceive<AreNoGreaterThan<1>::Mold, Vay<Args>...>
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
template<auto...Arg>
concept GreaterThanTwoA
= (...||(not AreNoGreaterThan<2>::Mold<Vay<Arg>>::value));

template<auto...Arg>
concept GreaterThanTwoB
= (...||(not AreNoGreaterThan<2>::Mold<Vay<Arg>>::value));

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
= AnyDeceive<AreNoGreaterThan<2>::Mold, Vay<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= AnyDeceive<AreNoGreaterThan<2>::Mold, Vay<Args>...>;

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