// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ALL_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_ALL_NEGATIVE_ONE_H

#include "conceptrodon/concepts/omennivore/all_valuable.hpp"
#include "conceptrodon/concepts/varybivore/all_negative_one.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept JustAllNegativeOne = Varybivore::AllNegativeOne<Args::value...>;

template<typename...Args>
concept AllNegativeOne
=   Omennivore::AllValuable<Args...>
&&  JustAllNegativeOne<Args...>;

}}

#endif