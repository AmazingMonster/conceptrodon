// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ANY_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_VARYBIVORE_ANY_NOT_NEGATIVE_ONE_H

#include "conceptrodon/metafunctions/varybivore/concepts/all_not_negative_one.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Args>
concept JustAnyNotNegativeOne = (...||(Args != -1));

template<auto...Args>
concept AnyNotNegativeOne
=   JustAnyNotNegativeOne<Args...>
||  AllNotNegativeOne<Args...>;

}}

#endif