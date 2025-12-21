// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOT_VARIADIC_H
#define CONCEPTRODON_FUNCTIVORE_NOT_VARIADIC_H

#include "conceptrodon/concepts/mouldivore/deceive.hpp"
#include "conceptrodon/metafunctions/functivore/is_variadic.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept NotVariadic
= Mouldivore::Deceive<IsVariadic, F>;

}}

#endif