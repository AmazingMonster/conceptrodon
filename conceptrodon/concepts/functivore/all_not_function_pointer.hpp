// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_NOT_FUNCTION_POINTER_H
#define CONCEPTRODON_FUNCTIVORE_ALL_NOT_FUNCTION_POINTER_H

#include "conceptrodon/concepts/mouldivore/all_failed.hpp"
#include "conceptrodon/metafunctions/functivore/is_function_pointer.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllNotFunctionPointer
= Mouldivore::AllFailed<IsFunctionPointer, Args...>;

}}

#endif