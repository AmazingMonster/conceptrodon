// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ALL_TYPICAL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ALL_TYPICAL_H

#include "conceptrodon/concepts/omennivore/all_typical.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestTypical {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool type = true;
};

static_assert(! AllTypical<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool type() {return true;};
};

static_assert(! AllTypical<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using type = int;
};

static_assert(AllTypical<Tester_2, Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    struct type {};
};

static_assert(AllTypical<Tester_3>);
static_assert(AllTypical<Tester_3, Tester_2>);
static_assert(! AllTypical<Tester, Tester_3, Tester_2>);
static_assert(! AllTypical<Tester_3, Tester_2, Tester>);
/******************************************************************************************************/




}}}}

#endif