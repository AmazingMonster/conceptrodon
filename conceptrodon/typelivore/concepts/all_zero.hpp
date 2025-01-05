// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ALL_ZERO_H
#define CONCEPTRODON_TYPELIVORE_ALL_ZERO_H

#include "conceptrodon/omennivore/concepts/all_valuable.hpp"
#include "conceptrodon/varybivore/concepts/all_zero.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept JustAllZero = Varybivore::AllZero<Args::value...>;

template<typename...Args>
concept AllZero
=   Omennivore::AllValuable<Args...>
&&  JustAllZero<Args...>;

}}

#endif