// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_PEG_NONZERO_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_PEG_NONZERO_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_peg_nonzero.hpp"
#include "conceptrodon/descend/typelivore/concepts/all_nonzero.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAllPegNonzero {




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
requires Typelivore::JustAllNonzero<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};

template<typename...Args>
requires AllPegNonzero<Args...>
struct Tester<Args...>
{
    static constexpr int value {3};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, Peg<0>>::value == 0);
static_assert(Tester<Peg<10>, Peg<0>>::value == 1);
static_assert(Tester<Monotony<1>, Peg<1>>::value == 2);
static_assert(Tester<Peg<1>, Peg<2>>::value == 3);
/******************************************************************************************************/




}}}}

#endif