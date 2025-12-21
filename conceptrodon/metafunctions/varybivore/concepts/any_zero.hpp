// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ANY_ZERO_H
#define CONCEPTRODON_VARYBIVORE_ANY_ZERO_H

#include "conceptrodon/metafunctions/varybivore/concepts/all_zero.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Args>
concept JustAnyZero = (...||(Args == 0));

template<auto...Args>
concept AnyZero
=   JustAnyZero<Args...>
||  AllZero<Args...>;

}}

#endif