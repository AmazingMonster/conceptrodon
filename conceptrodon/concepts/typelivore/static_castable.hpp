// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_STATIC_CASTABLE_H
#define CONCEPTRODON_TYPELIVORE_STATIC_CASTABLE_H

#include "conceptrodon/concepts/typelivore/nice.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typelivore {

template<typename From, typename To>
concept StaticCastable = Nice<decltype(static_cast<To>(std::declval<From>()))>;

}}

#endif