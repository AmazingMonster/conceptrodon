// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_PEG_ZERO_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_PEG_ZERO_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_peg_zero.hpp"
#include "conceptrodon/descend/typelivore/concepts/all_zero.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAllPegZero {




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
requires Typelivore::JustAllZero<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};

template<typename...Args>
requires AllPegZero<Args...>
struct Tester<Args...>
{
    static constexpr int value {3};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, Peg<0>>::value == 0);
static_assert(Tester<Peg<10>, Peg<0>>::value == 1);
static_assert(Tester<Monotony<0>, Peg<0>>::value == 2);
static_assert(Tester<Peg<0>, Peg<0>>::value == 3);
/******************************************************************************************************/




}}}}

#endif