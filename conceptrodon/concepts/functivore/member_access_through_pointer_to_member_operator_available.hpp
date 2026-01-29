// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_MEMBER_ACCESS_THROUGH_POINTER_TO_MEMBER_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_MEMBER_ACCESS_THROUGH_POINTER_TO_MEMBER_OPERATOR_AVAILABLE_H

#include "conceptrodon/concepts/typelivore/nice.hpp"
#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename Class, typename Member, typename...Args>
concept MemberAccessThroughPointerToMemberOperatorAvailable
= Typelivore::Nice<decltype((std::declval<Class>()->*std::declval<Member>())(std::declval<Args>()...))>;

}}

#endif