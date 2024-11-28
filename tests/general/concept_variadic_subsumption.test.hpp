// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_GENERAL_CONCEPT_SUBSUMPTION_H
#define CONCEPTRODON_TESTS_GENERAL_CONCEPT_SUBSUMPTION_H

namespace Conceptrodon {
namespace GeneralTests {
namespace ConceptSubsumption {

/******************************************************************************************************/
template<auto...Args>
concept C = true;

template<auto...Args>
struct Tester {};

template<auto First, auto...Args>
requires C<First>
struct Tester<First, Args...>
{
    static constexpr int value {0};
};

template<auto First, auto...Args>
requires C<First> && C<Args...>
struct Tester<First, Args...>
{
    static constexpr int value {1};
};

// static_assert(Tester<0, 0>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Args>
concept VariadicC = true;

template<auto First, auto...Args>
requires C<First> && VariadicC<Args...>
struct Tester<First, Args...>
{
    static constexpr int value {2};
};

// static_assert(Tester<0, 0>::value == 2);
/******************************************************************************************************/

}}}

#endif