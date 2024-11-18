// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ZERO_H
#define CONCEPTRODON_TYPELIVORE_ZERO_H

#include "conceptrodon/descend/varybivore/concepts/equal.hpp"
#include "conceptrodon/descend/omennivore/concepts/valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename Arg>
concept Zero
=   Omennivore::Valuable<Arg>
&&  Varybivore::Equal<Arg::value, 0>;

}}

#endif