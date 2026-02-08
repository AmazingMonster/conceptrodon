// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_MEMBER_ACCESS_THROUGH_POINTER_TO_MEMBER_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_MEMBER_ACCESS_THROUGH_POINTER_TO_MEMBER_OPERATOR_AVAILABLE_H

#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename Class, template<typename...> class Predicate, typename Member, typename...Args>
concept ReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable
= Predicate<decltype((std::declval<Class>()->*std::declval<Member>())(std::declval<Args>()...))>::value;

}}

#endif