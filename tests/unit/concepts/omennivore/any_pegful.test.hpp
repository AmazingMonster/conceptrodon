// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_PEGFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_PEGFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_pegful.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAnyPegful {




/******************************************************************************************************/
template<typename...>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyPegful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllPegful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Peg<10>, int>::value == 1);
static_assert(Tester<Peg<10>, Peg<0>>::value == 2);
/******************************************************************************************************/




}}}}

#endif