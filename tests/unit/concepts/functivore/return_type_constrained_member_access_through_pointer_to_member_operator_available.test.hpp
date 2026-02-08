// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_MEMBER_ACCESS_THROUGH_POINTER_TO_MEMBER_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_UNIT_TESTS_TEST_RETURN_TYPE_CONSTRAINED_MEMBER_ACCESS_THROUGH_POINTER_TO_MEMBER_OPERATOR_AVAILABLE_H

#include "conceptrodon/concepts/functivore/return_type_constrained_member_access_through_pointer_to_member_operator_available.hpp"
#include "conceptrodon/metafunctions/typelivore/is_same_as.hpp"
#include <functional>

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable {




/******************************************************************************************************/
struct Caller
{
    virtual void fun(int, int*) {}
};

template<typename C>
struct CustomPointer
{
    template<typename R, typename...Ps>
    std::function<R(Ps...)> operator->*(R(C::*fun)(Ps...)) const
    {
        return [fun, this](Ps...ps) -> R
        {
            return (c->*fun)(std::forward<Ps>(ps)...);
        };
    }
    
    template<typename R, typename...Ps>
    std::function<R(Ps...)> operator->*(R(C::*fun)(Ps...) const) const
    {
        return [fun, this](Ps...ps) -> R
        {
            return (c->*fun)(std::forward<Ps>(ps)...);
        };
    }

    C& operator*() { return *c; }

    C* c;
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(ReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable<Caller*, Typelivore::IsSameAs<void>::Mold, decltype(&Caller::fun), int, int*>);
static_assert(ReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable<CustomPointer<Caller>, Typelivore::IsSameAs<void>::Mold, decltype(&Caller::fun), int, int*>);
static_assert(not ReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable<CustomPointer<Caller>, Typelivore::IsSameAs<void>::Mold, decltype(&Caller::fun), int, int>);
static_assert(not ReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable<CustomPointer<Caller>, Typelivore::IsSameAs<bool>::Mold, decltype(&Caller::fun), int, int>);
/******************************************************************************************************/




}}}}

#endif