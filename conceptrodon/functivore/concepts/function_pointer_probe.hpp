// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_FUNCTION_POINTER_PROBE_H
#define CONCEPTRODON_FUNCTIVORE_FUNCTION_POINTER_PROBE_H

#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include "conceptrodon/functivore/is_function_pointer.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename FP>
concept FunctionPointerProbe
= Mouldivore::Confess<IsFunctionPointer, FP>;

}}

#endif