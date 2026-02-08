// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_MEMBER_FUNCTION_AT_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_MEMBER_FUNCTION_AT_AVAILABLE_H

#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename Class, template<typename...> class Predicate, typename...Args>
concept ReturnTypeConstrainedMemberFunctionAtAvailable
= Predicate<decltype(std::declval<Class>().at(std::declval<Args>()...))>::value;

}}

#endif