// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNVALUABLE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNVALUABLE_H

#include "conceptrodon/omennivore/concepts/descend/descend//any_unvaluable.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAnyUnvaluable {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

INVALID(AnyUnvaluable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

VALID(AnyUnvaluable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

VALID(AnyUnvaluable<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

VALID(AnyUnvaluable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

VALID(AnyUnvaluable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

INVALID(AnyUnvaluable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

VALID(AnyUnvaluable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

VALID(AnyUnvaluable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Examiner {};

template<typename...Args>
requires AnyUnvaluable<Args...>
struct Examiner<Args...>
{static constexpr bool value {false}; };

template<typename...Args>
requires AllUnvaluable<Args...>
struct Examiner<Args...>
{static constexpr bool value {true}; };

VALID(Examiner<Tester_2, Tester_1>::value);
INVALID(Examiner<Tester, Tester_1>::value);
INVALID(Examiner<Tester_1, Tester>::value);
/******************************************************************************************************/




}}}}

#endif