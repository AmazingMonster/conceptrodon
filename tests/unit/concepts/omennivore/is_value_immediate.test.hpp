// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_VALUE_IMMEDIATE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_VALUE_IMMEDIATE_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestIsValueImmediate {
namespace {




/******************************************************************************************************/
constexpr bool value_0 {true};
VALID(Ominuci::isValueImmediate(value_0));
/******************************************************************************************************/




/******************************************************************************************************/
bool value_1 {true};
// VALID(Ominuci::isValueImmediate(value_1));
/******************************************************************************************************/




/******************************************************************************************************/
void func() {};
VALID(Ominuci::isValueImmediate(func));
/******************************************************************************************************/




/******************************************************************************************************/
template<auto>
constexpr bool Truth = true;
VALID(Truth<func>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

VALID(Ominuci::isValueImmediate(Tester::value));
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static bool value;
};

// VALID(Ominuci::isValueImmediate(Tester_1::value));
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    static const bool value {true};
};

VALID(Ominuci::isValueImmediate(Tester_2::value));
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    static void func(){};
};

VALID(Truth<Tester_3::func>);
VALID(Ominuci::isValueImmediate(Tester_3::func));
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    static const float value;
};

const float Tester_4::value = 1.11;

// VALID(Ominuci::isValueImmediate(Tester_4::value));
/******************************************************************************************************/

}}}}}

#endif