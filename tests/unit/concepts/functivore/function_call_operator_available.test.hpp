// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_FUNCTION_CALL_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_FUNCTION_CALL_OPERATOR_AVAILABLE_H

#include "conceptrodon/concepts/functivore/function_call_operator_available.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestFunctionCallOperatorAvailable {




/******************************************************************************************************/
struct Caller
{
    void operator()(int, int*) {}
};

inline void fun(int, int*) {}
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(FunctionCallOperatorAvailable<Caller, int, int*>);
static_assert(not FunctionCallOperatorAvailable<Caller, int, int*, int**>);
static_assert(FunctionCallOperatorAvailable<decltype(fun), int, int*>);
static_assert(not FunctionCallOperatorAvailable<decltype(fun), int, int*, int**>);
/******************************************************************************************************/




}}}}

#endif