// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_TYPICAL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_TYPICAL_H

#include "conceptrodon/omennivore/concepts/typical.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestTypical {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool type = true;
};

static_assert(! Typical<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool type() {return true;};
};

static_assert(! Typical<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using type = int;
};

static_assert(Typical<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    struct type {};
};

static_assert(Typical<Tester_3>);
/******************************************************************************************************/




}}}}

#endif