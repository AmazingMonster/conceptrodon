// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_STATIC_CASTABLE_TO_BOOL_H
#define CONCEPTRODON_TYPELIVORE_STATIC_CASTABLE_TO_BOOL_H

#include "conceptrodon/concepts/typelivore/nice.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typelivore {

template<typename Type>
concept StaticCastableToBool = Nice<decltype(static_cast<bool>(std::declval<Type>()))>;

}}

#endif