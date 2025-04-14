// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_VARIADIC_H
#define CONCEPTRODON_FUNCTIVORE_ALL_VARIADIC_H

#include "conceptrodon/mouldivore/concepts/all_confess.hpp"
#include "conceptrodon/functivore/is_variadic.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllVariadic
= Mouldivore::AllConfess<IsVariadic, Args...>;

}}

#endif