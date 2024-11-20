// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ZERO_H
#define CONCEPTRODON_TYPELIVORE_ZERO_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/equal.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Arg>
concept JustZero = Varybivore::Equal<Arg::value, 0>;

template<typename Arg>
concept Zero
=   Omennivore::Valuable<Arg>
&&  JustZero<Arg>;

}}

#endif