// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_FUNCTION_CALL_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_FUNCTION_CALL_OPERATOR_AVAILABLE_H

#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename FunctionObject, template<typename...> class Predicate, typename...Args>
concept ReturnTypeConstrainedFunctionCallOperatorAvailable
= Predicate<decltype(std::declval<FunctionObject>()(std::declval<Args>()...))>::value;

}}

#endif