// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_MEMBER_FUNCTION_AT_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_MEMBER_FUNCTION_AT_AVAILABLE_H

#include "conceptrodon/concepts/functivore/member_function_at_available.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestMemberFunctionAtAvailable {




/******************************************************************************************************/
struct Caller
{
    void at(int, int*) {}
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(MemberFunctionAtAvailable<Caller, int, int*>);
static_assert(not MemberFunctionAtAvailable<Caller, int, int*, int**>);
/******************************************************************************************************/




}}}}

#endif