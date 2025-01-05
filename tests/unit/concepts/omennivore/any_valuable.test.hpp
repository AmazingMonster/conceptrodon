// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_VALUABLE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_VALUABLE_H

#include "conceptrodon/omennivore/concepts/any_valuable.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestValuable {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

static_assert(AnyValuable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

static_assert(! AnyValuable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

static_assert(! AnyValuable<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

static_assert(! AnyValuable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

static_assert(! AnyValuable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

static_assert(AnyValuable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

static_assert(! AnyValuable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

static_assert(! AnyValuable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Examiner {};

template<typename...Args>
requires AnyValuable<Args...>
struct Examiner<Args...>
{static constexpr bool value {false}; };

template<typename...Args>
requires AllValuable<Args...>
struct Examiner<Args...>
{static constexpr bool value {true}; };

static_assert(Examiner<Tester, Tester_5>::value);
static_assert(! Examiner<Tester, Tester_4>::value);
static_assert(! Examiner<Tester_4, Tester>::value);
/******************************************************************************************************/




}}}}

#endif