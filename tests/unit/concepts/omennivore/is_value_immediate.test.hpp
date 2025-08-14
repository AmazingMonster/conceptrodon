// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_VALUE_IMMEDIATE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_VALUE_IMMEDIATE_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestIsValueImmediate {
namespace {




/******************************************************************************************************/
constexpr bool value_0 {true};
static_assert(Ominuci::is_value_immediate(value_0));
/******************************************************************************************************/




/******************************************************************************************************/
bool value_1 {true};
// static_assert(Ominuci::is_value_immediate(value_1));
/******************************************************************************************************/




/******************************************************************************************************/
void func() {};
static_assert(Ominuci::is_value_immediate(func));
/******************************************************************************************************/




/******************************************************************************************************/
template<auto>
constexpr bool Truth = true;
static_assert(Truth<func>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

static_assert(Ominuci::is_value_immediate(Tester::value));
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static bool value;
};

// static_assert(Ominuci::is_value_immediate(Tester_1::value));
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    static const bool value {true};
};

static_assert(Ominuci::is_value_immediate(Tester_2::value));
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    static void func(){};
};

static_assert(Truth<Tester_3::func>);
static_assert(Ominuci::is_value_immediate(Tester_3::func));
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    static const float value;
};

const float Tester_4::value = 1.11;

// static_assert(Ominuci::is_value_immediate(Tester_4::value));
/******************************************************************************************************/

}}}}}

#endif