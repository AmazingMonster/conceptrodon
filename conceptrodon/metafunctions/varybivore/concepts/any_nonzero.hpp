// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ANY_NONZERO_H
#define CONCEPTRODON_VARYBIVORE_ANY_NONZERO_H

#include "conceptrodon/metafunctions/varybivore/concepts/all_nonzero.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Args>
concept JustAnyNonzero = (...||(Args != 0));

template<auto...Args>
concept AnyNonzero
=   JustAnyNonzero<Args...>
||  AllNonzero<Args...>;

}}

#endif