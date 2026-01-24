// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GENERAL_TESTS_CONCEPT_SUBSUMPTION_H
#define CONCEPTRODON_GENERAL_TESTS_CONCEPT_SUBSUMPTION_H

namespace Conceptrodon {
namespace GeneralTests {
namespace ConceptSubsumption {

/******************************************************************************************************/
template<auto...>
struct True
{
    static constexpr bool value {true};
};

template<auto...Args>
concept CA = True<Args...>::value;

template<auto...Args>
concept CB = True<Args...>::value;

template<auto...Args>
concept CC = True<Args...>::value;

template<auto...Args>
concept CD = True<Args...>::value;

template<auto...Args>
struct Tester {};

template<auto...Args>
requires CA<Args...>
struct Tester<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires CA<Args...> || CB<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

static_assert(Tester<0>::value == 0);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
requires CA<Args...> && CB<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};

static_assert(Tester<0>::value == 0);
static_assert(Tester<1>::value == 2);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
struct TesterB {};

template<auto...Args>
requires CA<Args...> || (CB<Args...> || CC<Args...>)
struct TesterB<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires CA<Args...> || (CB<Args...> && CD<Args...>)
struct TesterB<Args...>
{
    static constexpr int value {1};
};

static_assert(TesterB<0>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto ArgA, auto ArgB, auto ArgC>
struct TesterC {};

template<auto ArgA, auto ArgB, auto ArgC>
requires CA<ArgA> || (CB<ArgB> || CC<ArgC>)
struct TesterC<ArgA, ArgB, ArgC>
{
    static constexpr int value {0};
};

template<auto ArgA, auto ArgB, auto ArgC>
requires CA<ArgA> || (CB<ArgB> && CD<ArgC>)
struct TesterC<ArgA, ArgB, ArgC>
{
    static constexpr int value {1};
};

static_assert(TesterC<0, 1, 2>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
struct TesterD {};

template<auto...Args>
requires CA<Args...> || CB<Args...> // #1
struct TesterD<Args...>
{
    static constexpr int value {0};
};

template<auto...Args>
requires (CA<Args...> && CB<Args...>) && (CA<Args...> && CB<Args...>) // #2
struct TesterD<Args...>
{
    static constexpr int value {1};
};

static_assert(TesterC<0, 1, 2>::value == 1);
/******************************************************************************************************/




}}}

#endif