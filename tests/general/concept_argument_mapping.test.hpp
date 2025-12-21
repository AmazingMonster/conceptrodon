// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GENERAL_TESTS_CONCEPT_ARGUMENT_MAPPING_H
#define CONCEPTRODON_GENERAL_TESTS_CONCEPT_ARGUMENT_MAPPING_H

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
struct Vay
{ static constexpr auto value {I}; };

static_assert(Tester<Vay<0>, Vay<1>>::value);

}}}

#endif