// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ASSIGNMENT_MEMBER_FUNCTION_GET_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_ASSIGNMENT_MEMBER_FUNCTION_GET_AVAILABLE_H

#include "conceptrodon/concepts/typelivore/nice.hpp"
#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename Class, typename...Args>
concept MemberFunctionGetAvailable
= Typelivore::Nice<decltype(std::declval<Class>().get(std::declval<Args>()...))>;

}}

#endif