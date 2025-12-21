// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PEG_NONZERO_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PEG_NONZERO_H

#include "conceptrodon/metafunctions/omennivore/concepts/peg_nonzero.hpp"
#include "conceptrodon/metafunctions/typelivore/concepts/nonzero.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestPegNonzero {




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
requires Typelivore::JustNonzero<Arg>
struct Tester<Arg>
{
    static constexpr int value {2};
};

template<typename Arg>
requires PegNonzero<Arg>
struct Tester<Arg>
{
    static constexpr int value {3};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int>::value == 0);
static_assert(Tester<Peg<0>>::value == 1);
static_assert(Tester<Vay<1>>::value == 2);
static_assert(Tester<Peg<10>>::value == 3);
/******************************************************************************************************/




}}}}

#endif