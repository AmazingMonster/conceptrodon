// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ALL_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_ALL_NOT_NEGATIVE_ONE_H

#include "conceptrodon/varybivore/concepts/all_not_negative_one.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename...Structures>
concept AllNotNegativeOne
=   Omennivore::AllValuable<Structures...>
&&  Varybivore::AllNotNegativeOne<Structures::value...>;

}}

#endif