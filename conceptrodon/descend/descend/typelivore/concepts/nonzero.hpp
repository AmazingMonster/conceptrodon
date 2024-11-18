// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NONZERO_H
#define CONCEPTRODON_TYPELIVORE_NONZERO_H

#include "conceptrodon/descend/varybivore/concepts/descend/unequal.hpp"
#include "conceptrodon/descend/omennivore/concepts/valuable.hpp"

namespace Conceptrodon {
namespace Typelivore {
    
template<typename Arg>
concept Nonzero
=   Omennivore::Valuable<Arg>
&&  Varybivore::Unequal<Arg::value, 0>;

}}

#endif