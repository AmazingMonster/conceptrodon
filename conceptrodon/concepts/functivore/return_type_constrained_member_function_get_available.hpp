// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_MEMBER_FUNCTION_GET_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_MEMBER_FUNCTION_GET_AVAILABLE_H

#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename Class, template<typename...> class Predicate, typename...Args>
concept ReturnTypeConstrainedMemberFunctionGetAvailable
= Predicate<decltype(std::declval<Class>().get(std::declval<Args>()...))>::value;

}}

#endif