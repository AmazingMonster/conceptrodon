// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNVALUABLE_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNVALUABLE_H

#include "conceptrodon/concepts/omennivore/unvaluable.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestUnvaluable {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

static_assert(! Unvaluable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

static_assert(Unvaluable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

static_assert(Unvaluable<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

static_assert(Unvaluable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

static_assert(Unvaluable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

static_assert(! Unvaluable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

static_assert(Unvaluable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

static_assert(Unvaluable<Tester_6>);
/******************************************************************************************************/

}}}}

#endif