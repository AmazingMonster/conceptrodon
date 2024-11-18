// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_NEGATIVE_ONE_H

#include "conceptrodon/descend/varybivore/concepts/equal.hpp"
#include "conceptrodon/descend/omennivore/concepts/valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename Arg>
concept NegativeOne
=   Omennivore::Valuable<Arg>
&&  Varybivore::Equal<Arg::value, -1>;

}}

#endif