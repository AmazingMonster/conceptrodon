// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_ALL_CONFESS_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_ALL_CONFESS_H

#include "conceptrodon/mouldivore/concepts/all_confess.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestAllConfess {

/******************************************************************************************************/
template<auto Target>
struct AreGreaterThan
{
    template<typename Element>
    struct ProtoMold
    {
        static constexpr bool value
        { Target < Element::value };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AllConfess<AreGreaterThan<0>::Mold, Monotony<1>, Monotony<2>, Monotony<3>>);
static_assert(! AllConfess<AreGreaterThan<0>::Mold, Monotony<0>, Monotony<2>, Monotony<3>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...>
struct Tester {};

template<auto...Args>
requires AllConfess<AreGreaterThan<0>::Mold, Monotony<Args>...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires AllConfess<AreGreaterThan<1>::Mold, Monotony<Args>...>
struct Tester<Args...>
{
    static constexpr int value {-1};
};

template<auto...Args>
requires AllConfess<AreGreaterThan<0>::Mold, Monotony<Args>...>
&& AllConfess<AreGreaterThan<1>::Mold, Monotony<Args>...>
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
= AllConfess<AreGreaterThan<1>::Mold, Monotony<Args>...>;


template<auto...Args>
requires AllConfess<AreGreaterThan<0>::Mold, Monotony<Args>...>
&& AllConfess<AreGreaterThan<1>::Mold, Monotony<Args>...>
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
= (...&&AreGreaterThan<1>::Mold<Monotony<Args>>::value);

template<auto...Args>
requires AllConfess<AreGreaterThan<0>::Mold, Monotony<Args>...>
&& AllConfess<AreGreaterThan<1>::Mold, Monotony<Args>...>
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
= (...&&AreGreaterThan<2>::Mold<Monotony<Args>>::value);

template<auto...Args>
concept GreaterThanTwoB
= (...&&AreGreaterThan<2>::Mold<Monotony<Args>>::value);

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
= AllConfess<AreGreaterThan<2>::Mold, Monotony<Args>...>;

template<auto...Args>
concept GreaterThanTwoD
= AllConfess<AreGreaterThan<2>::Mold, Monotony<Args>...>;

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