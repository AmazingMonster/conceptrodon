// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ZERO_VALUE_H
#define CONCEPTRODON_OMENNIVORE_ZERO_VALUE_H

#include "conceptrodon/varybivore/concepts/equal.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept ZeroValue = Valuable<Arg> && Varybivore::Equal<Arg::value, 0>;

}}

#endif