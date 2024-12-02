// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNTYPICAL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNTYPICAL_H

#include "conceptrodon/omennivore/concepts/descend/descend/any_untypical.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAnyUntypical {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool type = true;
};

static_assert(AnyUntypical<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool type() {return true;};
};

static_assert(AnyUntypical<Tester_1>);
static_assert(AnyUntypical<Tester, Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using type = int;
};

static_assert(! AnyUntypical<Tester_2, Tester_2>);
static_assert(AnyUntypical<Tester_2, Tester_1>);
static_assert(AnyUntypical<Tester_1, Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    struct type {};
};

static_assert(! AnyUntypical<Tester_3>);
static_assert(! AnyUntypical<Tester_3, Tester_2>);
static_assert(AnyUntypical<Tester, Tester_3, Tester_2>);
static_assert(AnyUntypical<Tester_3, Tester_2, Tester>);
/******************************************************************************************************/




}}}}

#endif