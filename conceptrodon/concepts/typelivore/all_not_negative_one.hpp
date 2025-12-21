// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ALL_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_ALL_NOT_NEGATIVE_ONE_H

#include "conceptrodon/concepts/omennivore/all_valuable.hpp"
#include "conceptrodon/concepts/varybivore/all_not_negative_one.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept JustAllNotNegativeOne = Varybivore::AllNotNegativeOne<Args::value...>;

template<typename...Args>
concept AllNotNegativeOne
=   Omennivore::AllValuable<Args...>
&&  JustAllNotNegativeOne<Args...>;

}}

#endif