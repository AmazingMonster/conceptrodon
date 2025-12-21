// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNPEGFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNPEGFUL_H

#include "conceptrodon/concepts/omennivore/unpegful.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestUnpegful {




/******************************************************************************************************/
template<typename...>
struct Tester
{
    static constexpr int value {0};
};

template<typename Arg>
requires Unpegful<Arg>
struct Tester<Arg>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int>::value == 1);
static_assert(Tester<Peg<10>>::value == 0);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename Arg>
requires Unpegful<Arg> && Mouldivore::Deceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>
struct Tester<Arg>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int>::value == 1);
static_assert(Tester<Peg<10>>::value == 0);
// static_assert(Tester<double>::value == 2);
/******************************************************************************************************/




}}}}

#endif