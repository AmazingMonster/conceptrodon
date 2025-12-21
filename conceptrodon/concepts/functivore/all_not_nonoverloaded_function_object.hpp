// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_NOT_NONOVERLOADED_FUNCTION_OBJECT_H
#define CONCEPTRODON_FUNCTIVORE_ALL_NOT_NONOVERLOADED_FUNCTION_OBJECT_H

#include "conceptrodon/concepts/functivore/not_nonoverloaded_function_object.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllNotNonoverloadedFunctionObject
= (...&&NotNonoverloadedFunctionObject<Args>);

}}

#endif