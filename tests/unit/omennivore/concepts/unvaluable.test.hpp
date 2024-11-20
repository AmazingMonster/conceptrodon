// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNVALUABLE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNVALUABLE_H

#include "conceptrodon/descend/omennivore/concepts/descend/unvaluable.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestUnvaluable {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

INVALID(Unvaluable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

VALID(Unvaluable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

VALID(Unvaluable<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

VALID(Unvaluable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

VALID(Unvaluable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

INVALID(Unvaluable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

VALID(Unvaluable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

VALID(Unvaluable<Tester_6>);
/******************************************************************************************************/

}}}}

#endif