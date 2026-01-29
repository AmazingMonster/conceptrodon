// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_MEMBER_FUNCTION_GET_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_MEMBER_FUNCTION_GET_AVAILABLE_H

#include "conceptrodon/concepts/functivore/member_function_get_available.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestMemberFunctionGetAvailable {




/******************************************************************************************************/
struct Caller
{
    void get(int, int*) {}
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(MemberFunctionGetAvailable<Caller, int, int*>);
static_assert(not MemberFunctionGetAvailable<Caller, int, int*, int**>);
/******************************************************************************************************/




}}}}

#endif