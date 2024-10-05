// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_NONZERO_VALUE_H
#define CONCEPTRODON_OMENNIVORE_NONZERO_VALUE_H

#include "conceptrodon/varybivore/concepts/descend/unequal.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept NonzeroValue = Valuable<Arg> && Varybivore::Unequal<Arg::value, 0>;

}}

#endif