// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_ANY_NOT_NEGATIVE_ONE_H

#include "conceptrodon/metafunctions/omennivore/concepts/all_valuable.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/any_not_negative_one.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept JustAnyNotNegativeOne = Varybivore::AnyNotNegativeOne<Args::value...>;

template<typename...Args>
concept AnyNotNegativeOne
=   Omennivore::AllValuable<Args...>
&&  JustAnyNotNegativeOne<Args...>;

}}

#endif