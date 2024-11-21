// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_VALUABLE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_VALUABLE_H

#include "conceptrodon/omennivore/concepts/descend/any_valuable.hpp"
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

VALID(AnyValuable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

INVALID(AnyValuable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

INVALID(AnyValuable<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

INVALID(AnyValuable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

INVALID(AnyValuable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

VALID(AnyValuable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

INVALID(AnyValuable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

INVALID(AnyValuable<Tester_6>);
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

VALID(Examiner<Tester, Tester_5>::value);
INVALID(Examiner<Tester, Tester_4>::value);
INVALID(Examiner<Tester_4, Tester>::value);
/******************************************************************************************************/




}}}}

#endif