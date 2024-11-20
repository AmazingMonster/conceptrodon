// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_GENERAL_CONCEPT_ARGUMENT_MAPPING_H
#define CONCEPTRODON_TESTS_GENERAL_CONCEPT_ARGUMENT_MAPPING_H

namespace Conceptrodon {
namespace GeneralTests {
namespace ConceptArgumentMapping {

template<auto...>
concept CA = true;

template<auto...>
concept CB = true;

template<typename...>
struct Tester {};

template<typename...Args>
requires CA<Args::value...>
struct Tester<Args...>
{
    static constexpr bool value {false};
};

template<typename...Args>
requires CA<Args::value...> && CB<Args::value...>
struct Tester<Args...>
{
    static constexpr bool value {true};
};

template<auto I>
struct Val
{ static constexpr auto value {I}; };

static_assert(Tester<Val<0>, Val<1>>::value);

}}}

#endif