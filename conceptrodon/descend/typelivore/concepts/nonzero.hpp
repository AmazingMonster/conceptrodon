// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NONZERO_H
#define CONCEPTRODON_TYPELIVORE_NONZERO_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/descend/unequal.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Arg>
concept JustNonzero = Varybivore::Unequal<Arg::value, 0>;

template<typename Arg>
concept Nonzero
=   Omennivore::Valuable<Arg>
&&  JustNonzero<Arg>;

}}

#endif