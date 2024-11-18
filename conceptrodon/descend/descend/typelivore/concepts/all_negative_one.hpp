// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ALL_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_ALL_NEGATIVE_ONE_H

#include "conceptrodon/varybivore/concepts/all_negative_one.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename...Structures>
concept AllNegativeOne
=   Omennivore::AllValuable<Structures...>
&&  Varybivore::AllNegativeOne<Structures::value...>;

}}

#endif