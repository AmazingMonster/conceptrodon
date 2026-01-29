// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_ASSIGNMENT_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_ASSIGNMENT_OPERATOR_AVAILABLE_H

#include "conceptrodon/concepts/functivore/assignment_operator_available.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestAssignmentOperatorAvailable {




/******************************************************************************************************/
/**** Dummy ****/
struct Dummy {};

/**** Tester ****/
struct Tester
{
    Tester& operator=(Tester const&);
    Tester& operator=(bool const&);
};

/**** Tester_1 ****/
struct Tester_1
{
    Tester_1& operator=(Tester_1 const&);
    Tester_1& operator=(Dummy const&);
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(AssignmentOperatorAvailable<int, int>);
static_assert(AssignmentOperatorAvailable<int, float>);
static_assert(AssignmentOperatorAvailable<int, int>);
static_assert(not AssignmentOperatorAvailable<int, Dummy>);
static_assert(AssignmentOperatorAvailable<Tester, Tester>);
static_assert(AssignmentOperatorAvailable<Tester, bool>);
static_assert(AssignmentOperatorAvailable<Tester, int>);
static_assert(AssignmentOperatorAvailable<Tester, std::true_type>);
static_assert(not AssignmentOperatorAvailable<Tester, Dummy>);
static_assert(AssignmentOperatorAvailable<Tester_1, Dummy>);
/******************************************************************************************************/




}}}}

#endif