// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_GENERAL_CONCEPT_ARGUMENT_ORDER_H
#define CONCEPTRODON_TESTS_GENERAL_CONCEPT_ARGUMENT_ORDER_H

namespace Conceptrodon {
namespace GeneralTests {
namespace ConceptArgumentOrder {

template<auto I, auto J>
concept CA = true;

template<auto I, auto J>
concept CB = CA<J, I>;

template<auto I, auto J>
struct Tester
{ static constexpr int value {0}; };

template<auto I, auto J>
requires CA<J, I>
struct Tester<I, J>
{ static constexpr int value {1}; };

template<auto I, auto J>
requires CA<J, I> && CB<I, J>
struct Tester<I, J>
{ static constexpr int value {2}; };

// static_assert(Tester<1, 1>::value == 2);

}}}

#endif