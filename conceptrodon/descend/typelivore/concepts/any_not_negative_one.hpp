// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_ANY_NOT_NEGATIVE_ONE_H

#include "conceptrodon/omennivore/concepts/all_valuable.hpp"
#include "conceptrodon/varybivore/concepts/descend/any_not_negative_one.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept JustAnyNotNegativeOne = Varybivore::JustAnyNotNegativeOne<Args::value...>;

template<typename...Args>
concept AnyNotNegativeOne
=   Omennivore::AllValuable<Args...>
&&  (JustAnyNotNegativeOne<Args...> || Varybivore::AllNotNegativeOne<Args::value...>);

}}

#endif