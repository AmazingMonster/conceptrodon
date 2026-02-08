// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_MEMBER_FUNCTION_GET_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_MEMBER_FUNCTION_GET_AVAILABLE_H

#include "conceptrodon/concepts/functivore/return_type_constrained_member_function_get_available.hpp"
#include "conceptrodon/metafunctions/typelivore/is_same_as.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestReturnTypeConstrainedMemberFunctionGetAvailable {




/******************************************************************************************************/
struct Caller
{
    void get(int, int*) {}
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(ReturnTypeConstrainedMemberFunctionGetAvailable<Caller, Typelivore::IsSameAs<void>::Mold, int, int*>);
static_assert(not ReturnTypeConstrainedMemberFunctionGetAvailable<Caller, Typelivore::IsSameAs<void>::Mold, int, int*, int**>);
static_assert(not ReturnTypeConstrainedMemberFunctionGetAvailable<Caller, Typelivore::IsSameAs<int>::Mold, int, int*, int**>);
/******************************************************************************************************/




}}}}

#endif