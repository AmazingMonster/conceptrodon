// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_ANY_NEGATIVE_ONE_H

#include "conceptrodon/varybivore/concepts/descend/any_negative_one.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename...Structures>
concept AnyNegativeOne
=   Omennivore::AllValuable<Structures...>
&&  Varybivore::AnyNegativeOne<Structures::value...>;

}}

#endif