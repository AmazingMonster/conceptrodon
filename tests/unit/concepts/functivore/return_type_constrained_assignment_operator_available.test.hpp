// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_ASSIGNMENT_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_ASSIGNMENT_OPERATOR_AVAILABLE_H

#include "conceptrodon/concepts/functivore/return_type_constrained_assignment_operator_available.hpp"
#include "conceptrodon/metafunctions/typelivore/is_same_as.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestReturnTypeConstrainedAssignmentOperatorAvailable {




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
static_assert(ReturnTypeConstrainedAssignmentOperatorAvailable<int, Typelivore::IsSameAs<int&>::Mold, int>);
static_assert(ReturnTypeConstrainedAssignmentOperatorAvailable<int, Typelivore::IsSameAs<int&>::Mold, float>);
static_assert(ReturnTypeConstrainedAssignmentOperatorAvailable<int, Typelivore::IsSameAs<int&>::Mold, int>);
static_assert(not ReturnTypeConstrainedAssignmentOperatorAvailable<int, Typelivore::IsSameAs<int&>::Mold, Dummy>);
static_assert(ReturnTypeConstrainedAssignmentOperatorAvailable<Tester, Typelivore::IsSameAs<Tester&>::Mold, Tester>);
static_assert(ReturnTypeConstrainedAssignmentOperatorAvailable<Tester, Typelivore::IsSameAs<Tester&>::Mold, bool>);
static_assert(ReturnTypeConstrainedAssignmentOperatorAvailable<Tester, Typelivore::IsSameAs<Tester&>::Mold, int>);
static_assert(ReturnTypeConstrainedAssignmentOperatorAvailable<Tester, Typelivore::IsSameAs<Tester&>::Mold, std::true_type>);
static_assert(not ReturnTypeConstrainedAssignmentOperatorAvailable<Tester, Typelivore::IsSameAs<Tester&>::Mold, Dummy>);
static_assert(ReturnTypeConstrainedAssignmentOperatorAvailable<Tester_1, Typelivore::IsSameAs<Tester_1&>::Mold, Dummy>);
/******************************************************************************************************/




}}}}

#endif