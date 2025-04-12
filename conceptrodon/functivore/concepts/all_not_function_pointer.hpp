// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_NOT_FUNCTION_POINTER_H
#define CONCEPTRODON_FUNCTIVORE_ALL_NOT_FUNCTION_POINTER_H

#include "conceptrodon/mouldivore/concepts/all_deceive.hpp"
#include "conceptrodon/functivore/is_function_pointer.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllNotFunctionPointer
= Mouldivore::AllDeceive<IsFunctionPointer, Args...>;

}}

#endif