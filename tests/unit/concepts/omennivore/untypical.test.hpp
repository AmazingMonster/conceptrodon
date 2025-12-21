// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNTYPICAL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNTYPICAL_H

#include "conceptrodon/concepts/omennivore/untypical.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestUntypical {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool type = true;
};

static_assert(Untypical<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool type() {return true;};
};

static_assert(Untypical<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using type = int;
};

static_assert(! Untypical<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    struct type {};
};

static_assert(! Untypical<Tester_3>);
/******************************************************************************************************/




}}}}

#endif