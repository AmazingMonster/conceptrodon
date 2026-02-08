// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_MEMBER_FUNCTION_AT_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_MEMBER_FUNCTION_AT_AVAILABLE_H

#include "conceptrodon/concepts/functivore/return_type_constrained_member_function_at_available.hpp"
#include "conceptrodon/metafunctions/typelivore/is_same_as.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestReturnTypeConstrainedMemberFunctionAtAvailable {




/******************************************************************************************************/
struct Caller
{
    void at(int, int*) {}
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(ReturnTypeConstrainedMemberFunctionAtAvailable<Caller, Typelivore::IsSameAs<void>::Mold, int, int*>);
static_assert(not ReturnTypeConstrainedMemberFunctionAtAvailable<Caller, Typelivore::IsSameAs<void>::Mold, int, int*, int**>);
static_assert(not ReturnTypeConstrainedMemberFunctionAtAvailable<Caller, Typelivore::IsSameAs<int>::Mold, int, int*, int**>);
/******************************************************************************************************/




}}}}

#endif