// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_ANY_NEGATIVE_ONE_H

#include "conceptrodon/omennivore/concepts/all_valuable.hpp"
#include "conceptrodon/varybivore/concepts/descend/any_negative_one.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept JustAnyNegativeOne = Varybivore::JustAnyNegativeOne<Args::value...>;

template<typename...Args>
concept AnyNegativeOne
=   Omennivore::AllValuable<Args...>
&&  (JustAnyNegativeOne<Args...> || Varybivore::AllNegativeOne<Args::value...>);

}}

#endif