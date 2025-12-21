// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PEGFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PEGFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/pegful.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestPegful {




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
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int>::value == 0);
static_assert(Tester<Peg<10>>::value == 1);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename Arg>
requires Pegful<Arg> && Mouldivore::Confess<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>
struct Tester<Arg>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int>::value == 0);
static_assert(Tester<Peg<10>>::value == 1);
// static_assert(Tester<Peg<11>>::value == 2);
/******************************************************************************************************/




}}}}

#endif