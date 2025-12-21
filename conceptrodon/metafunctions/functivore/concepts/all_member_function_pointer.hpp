// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_MEMBER_FUNCTION_POINTER_H
#define CONCEPTRODON_FUNCTIVORE_ALL_MEMBER_FUNCTION_POINTER_H

#include "conceptrodon/metafunctions/mouldivore/concepts/all_confess.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllMemberFunctionPointer
= Mouldivore::AllConfess<std::is_member_function_pointer, Args...>;

}}

#endif