// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_PEG_ZERO_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_PEG_ZERO_H

#include "conceptrodon/omennivore/concepts/any_peg_zero.hpp"
#include "conceptrodon/omennivore/concepts/all_pegful.hpp"
#include "conceptrodon/typelivore/concepts/any_zero.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAnyPegZero {




/******************************************************************************************************/
template<typename...>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AllPegful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires Typelivore::JustAnyZero<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};

template<typename...Args>
requires AnyPegZero<Args...>
struct Tester<Args...>
{
    static constexpr int value {3};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, Peg<0>>::value == 0);
static_assert(Tester<Peg<10>, Peg<1>>::value == 1);
static_assert(Tester<Vay<0>, Peg<10>>::value == 2);
static_assert(Tester<Peg<0>, Peg<1>>::value == 3);
/******************************************************************************************************/




}}}}

#endif