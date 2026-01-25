// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOT_FUNCTION_POINTER_H
#define CONCEPTRODON_FUNCTIVORE_NOT_FUNCTION_POINTER_H

#include "conceptrodon/concepts/mouldivore/failed.hpp"
#include "conceptrodon/metafunctions/functivore/is_function_pointer.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename FP>
concept NotFunctionPointer
= Mouldivore::Failed<IsFunctionPointer, FP>;

}}

#endif