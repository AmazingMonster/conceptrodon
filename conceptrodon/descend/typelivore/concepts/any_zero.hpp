// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_ZERO_H
#define CONCEPTRODON_TYPELIVORE_ANY_ZERO_H

#include "conceptrodon/omennivore/concepts/all_valuable.hpp"
#include "conceptrodon/varybivore/concepts/descend/any_zero.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept JustAnyZero = Varybivore::AnyZero<Args::value...>;

template<typename...Args>
concept AnyZero
=   Omennivore::AllValuable<Args...>
&&  JustAnyZero<Args...>;

}}

#endif