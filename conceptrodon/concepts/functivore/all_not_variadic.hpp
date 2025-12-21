// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_NOT_VARIADIC_H
#define CONCEPTRODON_FUNCTIVORE_ALL_NOT_VARIADIC_H

#include "conceptrodon/concepts/mouldivore/all_deceive.hpp"
#include "conceptrodon/metafunctions/functivore/is_variadic.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllNotVariadic
= Mouldivore::AllDeceive<IsVariadic, Args...>;

}}

#endif