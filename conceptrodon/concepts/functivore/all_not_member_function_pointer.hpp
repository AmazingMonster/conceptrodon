// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_NOT_MEMBER_FUNCTION_POINTER_H
#define CONCEPTRODON_FUNCTIVORE_ALL_NOT_MEMBER_FUNCTION_POINTER_H

#include "conceptrodon/concepts/mouldivore/all_deceive.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllNotMemberFunctionPointer
= Mouldivore::AllDeceive<std::is_member_function_pointer, Args...>;

}}

#endif