// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ALL_NONZERO_H
#define CONCEPTRODON_TYPELIVORE_ALL_NONZERO_H

#include "conceptrodon/varybivore/concepts/all_nonzero.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename...Structures>
concept AllNonzero
=   Omennivore::AllValuable<Structures...>
&&  Varybivore::AllNonzero<Structures::value...>;

}}

#endif