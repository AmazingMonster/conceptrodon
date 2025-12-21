// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NONZERO_H
#define CONCEPTRODON_TYPELIVORE_NONZERO_H

#include "conceptrodon/concepts/omennivore/valuable.hpp"
#include "conceptrodon/concepts/varybivore/unequal_to.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Arg>
concept JustNonzero = Varybivore::UnequalTo<Arg::value, 0>;

template<typename Arg>
concept Nonzero
=   Omennivore::Valuable<Arg>
&&  JustNonzero<Arg>;

}}

#endif