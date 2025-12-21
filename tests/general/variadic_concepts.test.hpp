// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GENERAL_TESTS_VARIADIC_CONCEPTS_H
#define CONCEPTRODON_GENERAL_TESTS_VARIADIC_CONCEPTS_H

namespace Conceptrodon {
namespace GeneralTests {
namespace VariadicConcepts {

template<auto I>
concept GreaterThanZero = (I>0);

template<auto I>
concept GreaterThanOne = (I>1);

template<auto...>
struct Tester {};

template<auto...I>
requires (...&&GreaterThanZero<I>)
struct Tester<I...>
{
    static constexpr bool value {false};
};

template<auto...I>
requires (...&&GreaterThanZero<I>) && (...&&GreaterThanOne<I>)
struct Tester<I...>
{
    static constexpr bool value {true};
};

// static_assert(Tester<10>::value);

}}}

#endif