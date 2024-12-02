// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_PEG_NONZERO_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_PEG_NONZERO_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_peg_nonzero.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_pegful.hpp"
#include "conceptrodon/descend/typelivore/concepts/any_nonzero.hpp"
#include "conceptrodon/monotony.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAnyPegNonzero {




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
requires Typelivore::JustAnyNonzero<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};

template<typename...Args>
requires AnyPegNonzero<Args...>
struct Tester<Args...>
{
    static constexpr int value {3};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, Peg<0>>::value == 0);
static_assert(Tester<Peg<0>, Peg<0>>::value == 1);
static_assert(Tester<Monotony<0>, Peg<10>>::value == 2);
static_assert(Tester<Peg<0>, Peg<1>>::value == 3);
/******************************************************************************************************/




}}}}

#endif