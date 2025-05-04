// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_MEMBER_FUNCTION_POINTER_PROBE_H
#define CONCEPTRODON_FUNCTIVORE_MEMBER_FUNCTION_POINTER_PROBE_H

#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Functivore {

template<typename FP>
concept MemberFunctionPointerProbe
= Mouldivore::Confess<std::is_member_function_pointer, FP>;

}}

#endif