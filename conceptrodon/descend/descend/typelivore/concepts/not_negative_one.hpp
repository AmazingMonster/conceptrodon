// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_NOT_NEGATIVE_ONE_H

#include "conceptrodon/descend/varybivore/concepts/descend/unequal.hpp"
#include "conceptrodon/descend/omennivore/concepts/valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename Arg>
concept NotNegativeOne
=   Omennivore::Valuable<Arg>
&&  Varybivore::Unequal<Arg::value, -1>;

}}

#endif