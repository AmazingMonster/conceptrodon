// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_NONOVERLOADED_FUNCTION_OBJECT_H
#define CONCEPTRODON_FUNCTIVORE_ALL_NONOVERLOADED_FUNCTION_OBJECT_H

#include "conceptrodon/concepts/functivore/nonoverloaded_function_object_probe.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllNonoverloadedFunctionObject
= (...&&NonoverloadedFunctionObjectProbe<Args>);

}}

#endif