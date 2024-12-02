// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNPEGFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNPEGFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_unpegful.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAnyUnpegful {




/******************************************************************************************************/
template<typename...>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnpegful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnpegful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Peg<10>, Peg<0>>::value == 0);
static_assert(Tester<Peg<10>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif