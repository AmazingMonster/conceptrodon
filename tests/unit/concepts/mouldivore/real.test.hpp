// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_REAL_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_REAL_H

#include "conceptrodon/mouldivore/concepts/real.hpp"
#include "conceptrodon/vay.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestReal {

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

template<auto...>
struct Tester {};

template<auto Arg>
requires Real<Vay<Arg>, AreGreaterThan<0>::Mold>
struct Tester<Arg>
{
    static constexpr int value {0};
};

template<auto Arg>
requires Real<Vay<Arg>, AreGreaterThan<1>::Mold>
struct Tester<Arg>
{
    static constexpr int value {-1};
};

template<auto Arg>
requires Real<Vay<Arg>, AreGreaterThan<0>::Mold>
&&  Real<Vay<Arg>, AreGreaterThan<1>::Mold>
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
std::true_type fun(Real<AreGreaterThan<0>::Mold> auto);
std::false_type fun(auto);
std::integral_constant<int, 10> fun(Real<AreGreaterThan<10>::Mold> auto);
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(decltype(fun(Vay<3>{}))::value);
static_assert(! decltype(fun(Vay<-3>{}))::value);
//static_assert(decltype(fun(Vay<11>{}))::value == 10);
/******************************************************************************************************/





}}}}

#endif