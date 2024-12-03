// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PEG_ZERO_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PEG_ZERO_H

#include "conceptrodon/descend/omennivore/concepts/descend/peg_zero.hpp"
#include "conceptrodon/descend/typelivore/concepts/zero.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestPegZero {




/******************************************************************************************************/
template<typename...>
struct Tester
{
    static constexpr int value {0};
};

template<typename Arg>
requires Pegful<Arg>
struct Tester<Arg>
{
    static constexpr int value {1};
};

template<typename Arg>
requires Typelivore::JustZero<Arg>
struct Tester<Arg>
{
    static constexpr int value {2};
};

template<typename Arg>
requires PegZero<Arg>
struct Tester<Arg>
{
    static constexpr int value {3};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int>::value == 0);
static_assert(Tester<Peg<10>>::value == 1);
static_assert(Tester<Vay<0>>::value == 2);
static_assert(Tester<Peg<0>>::value == 3);
/******************************************************************************************************/




}}}}

#endif