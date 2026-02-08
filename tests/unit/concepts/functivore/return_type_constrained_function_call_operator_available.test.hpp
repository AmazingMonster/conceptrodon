// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_FUNCTION_CALL_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_FUNCTION_CALL_OPERATOR_AVAILABLE_H

#include "conceptrodon/concepts/functivore/return_type_constrained_function_call_operator_available.hpp"
#include "conceptrodon/metafunctions/typelivore/is_same_as.hpp"

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestReturnTypeConstrainedFunctionCallOperatorAvailable {




/******************************************************************************************************/
struct Caller
{
    void operator()(int, int*) {}
};

inline void fun(int, int*) {}
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(ReturnTypeConstrainedFunctionCallOperatorAvailable<Caller, Typelivore::IsSameAs<void>::Mold, int, int*>);
static_assert(not ReturnTypeConstrainedFunctionCallOperatorAvailable<Caller, Typelivore::IsSameAs<int>::Mold, int, int*>);
static_assert(not ReturnTypeConstrainedFunctionCallOperatorAvailable<Caller, Typelivore::IsSameAs<void>::Mold, int, int*, int**>);
static_assert(ReturnTypeConstrainedFunctionCallOperatorAvailable<decltype(fun), Typelivore::IsSameAs<void>::Mold, int, int*>);
static_assert(not ReturnTypeConstrainedFunctionCallOperatorAvailable<decltype(fun), Typelivore::IsSameAs<void>::Mold, int, int*, int**>);
/******************************************************************************************************/




}}}}

#endif