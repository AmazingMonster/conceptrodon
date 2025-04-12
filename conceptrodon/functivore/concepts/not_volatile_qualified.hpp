// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOT_VOLATILE_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_NOT_VOLATILE_QUALIFIED_H

#include "conceptrodon/mouldivore/concepts/deceive.hpp"
#include "conceptrodon/functivore/is_volatile.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept NotVolatileQualified
= Mouldivore::Deceive<IsVolatile, F>;

}}

#endif