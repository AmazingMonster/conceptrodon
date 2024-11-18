// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_NONZERO_H
#define CONCEPTRODON_TYPELIVORE_ANY_NONZERO_H

#include "conceptrodon/varybivore/concepts/descend/any_nonzero.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename...Structures>
concept AnyNonzero
=   Omennivore::AllValuable<Structures...>
&&  Varybivore::AnyNonzero<Structures::value...>;

}}

#endif