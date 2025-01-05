// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ANY_NEGATIVE_ONE_H
#define CONCEPTRODON_VARYBIVORE_ANY_NEGATIVE_ONE_H

#include "conceptrodon/varybivore/concepts/all_negative_one.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Args>
concept JustAnyNegativeOne = (...||(Args == -1));

template<auto...Args>
concept AnyNegativeOne
=   JustAnyNegativeOne<Args...>
||  AllNegativeOne<Args...>;

}}

#endif