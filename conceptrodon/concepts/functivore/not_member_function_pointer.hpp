// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOT_MEMBER_FUNCTION_POINTER_H
#define CONCEPTRODON_FUNCTIVORE_NOT_MEMBER_FUNCTION_POINTER_H

#include "conceptrodon/concepts/mouldivore/deceive.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Functivore {

template<typename MFP>
concept NotMemberFunctionPointer
= Mouldivore::Deceive<std::is_member_function_pointer, MFP>;

}}

#endif