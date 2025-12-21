// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNVALUABLE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNVALUABLE_H

#include "conceptrodon/concepts/omennivore/all_unvaluable.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAllUnvaluable {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

static_assert(! AllUnvaluable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

static_assert(AllUnvaluable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

static_assert(AllUnvaluable<Tester_2, Tester_1>);
static_assert(! AllUnvaluable<Tester, Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

static_assert(AllUnvaluable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

static_assert(AllUnvaluable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

static_assert(! AllUnvaluable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

static_assert(AllUnvaluable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

static_assert(AllUnvaluable<Tester_6>);
/******************************************************************************************************/





/******************************************************************************************************/
static_assert(! AllUnvaluable<Tester_5, Tester_6>);
static_assert(! AllUnvaluable<Tester_6, Tester_5>);
/******************************************************************************************************/




}}}}

#endif