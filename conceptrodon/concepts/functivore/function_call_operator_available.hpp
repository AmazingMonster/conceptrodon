// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_FUNCTION_CALL_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_FUNCTION_CALL_OPERATOR_AVAILABLE_H

#include "conceptrodon/concepts/typelivore/nice.hpp"
#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename FunctionObject, typename...Args>
concept FunctionCallOperatorAvailable
= Typelivore::Nice<decltype(std::declval<FunctionObject>()(std::declval<Args>()...))>;

}}

#endif