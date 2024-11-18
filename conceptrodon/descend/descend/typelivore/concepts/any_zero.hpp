// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_ZERO_H
#define CONCEPTRODON_TYPELIVORE_ANY_ZERO_H

#include "conceptrodon/varybivore/concepts/descend/any_zero.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename...Structures>
concept AnyZero
=   Omennivore::AllValuable<Structures...>
&&  Varybivore::AnyZero<Structures::value...>;

}}

#endif