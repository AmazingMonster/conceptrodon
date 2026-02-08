// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_MEMBER_FUNCTION_AT_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_MEMBER_FUNCTION_AT_AVAILABLE_H

#include "conceptrodon/concepts/typelivore/nice.hpp"
#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename Class, typename...Args>
concept MemberFunctionAtAvailable
= Typelivore::Nice<decltype(std::declval<Class>().at(std::declval<Args>()...))>;

}}

#endif