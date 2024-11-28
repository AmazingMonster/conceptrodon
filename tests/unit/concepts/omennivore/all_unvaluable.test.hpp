// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNVALUABLE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNVALUABLE_H

#include "conceptrodon/omennivore/concepts/descend/all_unvaluable.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAllUnvaluable {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

INVALID(AllUnvaluable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

VALID(AllUnvaluable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

VALID(AllUnvaluable<Tester_2, Tester_1>);
VALID(! AllUnvaluable<Tester, Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

VALID(AllUnvaluable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

VALID(AllUnvaluable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

INVALID(AllUnvaluable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

VALID(AllUnvaluable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

VALID(AllUnvaluable<Tester_6>);
/******************************************************************************************************/





/******************************************************************************************************/
INVALID(AllUnvaluable<Tester_5, Tester_6>);
INVALID(AllUnvaluable<Tester_6, Tester_5>);
/******************************************************************************************************/





}}}}

#endif