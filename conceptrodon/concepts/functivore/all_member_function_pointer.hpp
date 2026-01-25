// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_MEMBER_FUNCTION_POINTER_H
#define CONCEPTRODON_FUNCTIVORE_ALL_MEMBER_FUNCTION_POINTER_H

#include "conceptrodon/concepts/mouldivore/all_passed.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllMemberFunctionPointer
= Mouldivore::AllPassed<std::is_member_function_pointer, Args...>;

}}

#endif