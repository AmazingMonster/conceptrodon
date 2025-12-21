// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNPEGFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNPEGFUL_H

#include "conceptrodon/concepts/omennivore/all_unpegful.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAllUnpegful {




/******************************************************************************************************/
template<typename...>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AllUnpegful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 1);
static_assert(Tester<Peg<10>, int>::value == 0);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
requires AllUnpegful<Args...> && Mouldivore::AllDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 1);
static_assert(Tester<Peg<10>, int>::value == 0);
// static_assert(Tester<double, int>::value == 2);
/******************************************************************************************************/




}}}}

#endif