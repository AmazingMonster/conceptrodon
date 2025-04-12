// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOT_NONOVERLOADED_FUNCTION_OBJECT_H
#define CONCEPTRODON_FUNCTIVORE_NOT_NONOVERLOADED_FUNCTION_OBJECT_H

namespace Conceptrodon {
namespace Functivore {

template<typename FO>
concept NotNonOverloadedFunctionObject
= ! requires {&FO::operator();};

}}

#endif