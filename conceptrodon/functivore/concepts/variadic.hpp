// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_VARIADIC_H
#define CONCEPTRODON_FUNCTIVORE_VARIADIC_H

#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include "conceptrodon/functivore/is_variadic.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept Variadic
= Mouldivore::Confess<IsVariadic, F>;

}}

#endif