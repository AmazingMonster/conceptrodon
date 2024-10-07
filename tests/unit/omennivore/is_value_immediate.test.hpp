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
namespace TestIsValueImmediate {

namespace 
{

struct Tester
{
    static constexpr bool value = true;
    static bool value_1() {return true;};
    static bool value_2 ;
    static const bool value_3 = true;

    static void func(){};

    static const float value_4;
};

bool Tester::value_2 {true};
const float Tester::value_4 = 1.111;
constexpr bool value_0 {true};

bool value_1 {true};

void func() {};

template<auto>
constexpr bool Truth = true;

}

VALID(Ominuci::isValueImmediate(value_0));
VALID(Ominuci::isValueImmediate(Tester::value));
VALID(Ominuci::isValueImmediate(Tester::value_3));
VALID(Ominuci::isValueImmediate(func));
VALID(Ominuci::isValueImmediate(Tester::func));
VALID(Truth<func>);
VALID(Truth<Tester::func>);
// VALID(isValueImmediate(Tester::value_4));
// VALID(isValueImmediate(Tester::value_2));
// VALID(isValueImmediate(value_1));

}}}

#endif