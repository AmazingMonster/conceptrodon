// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_VALUABLE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_VALUABLE_H

#include "conceptrodon/descend/omennivore/concepts/all_valuable.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestValuable {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

VALID(AllValuable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

INVALID(AllValuable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

INVALID(AllValuable<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

INVALID(AllValuable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

INVALID(AllValuable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

VALID(AllValuable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

INVALID(AllValuable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

INVALID(AllValuable<Tester_6>);
/******************************************************************************************************/




}}}}

#endif