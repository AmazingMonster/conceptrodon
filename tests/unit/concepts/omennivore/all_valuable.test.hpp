// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ALL_VALUABLE_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ALL_VALUABLE_H

#include "conceptrodon/concepts/omennivore/all_valuable.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestValuable {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

static_assert(AllValuable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

static_assert(! AllValuable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

static_assert(! AllValuable<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

static_assert(! AllValuable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

static_assert(! AllValuable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

static_assert(AllValuable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

static_assert(! AllValuable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

static_assert(! AllValuable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AllValuable<Tester_5, Tester>);
static_assert(! AllValuable<Tester_6, Tester_5>);
static_assert(! AllValuable<Tester_5, Tester_6>);
/******************************************************************************************************/




}}}}

#endif